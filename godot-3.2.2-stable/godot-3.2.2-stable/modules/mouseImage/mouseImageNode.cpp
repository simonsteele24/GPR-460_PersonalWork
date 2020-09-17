#include "mouseImageNode.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"
#include "scene/main/viewport.h"

MouseImageNode::MouseImageNode()
{
	canvas = VisualServer::get_singleton()->canvas_item_create();
	frame = 0;
	vframes = 1;
	hframes = 1;
	centered = true;
}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("path", "a"), &MouseImageNode::path);
	ClassDB::bind_method(D_METHOD("location", "a"), &MouseImageNode::location);
	ClassDB::bind_method(D_METHOD("draw"), &MouseImageNode::draw);
}


//Custom Functions
void MouseImageNode::path(String a) {
	imagePath = a;
}

void MouseImageNode::location(Point2 newLocation)
{
	iconLocationX = newLocation.x;
	iconLocationY = newLocation.y;
}

Point2 MouseImageNode::getMouseLocation()
{
	return OS::get_singleton()->get_mouse_position();
}

void MouseImageNode::draw()
{
	Ref<Image> img;
	img.instance();
	img->load(imagePath);
	Ref<ImageTexture> newTex;
	newTex.instance();
	newTex->create_from_image(img);
	set_texture(newTex);
	set_offset(getMouseLocation());
}

void MouseImageNode::_notification(int p_what)
{
	switch (p_what) {

		case NOTIFICATION_DRAW: {
			if (texture.is_null())
				return;
			RID ci = get_canvas_item();
			Rect2 src_rect, dst_rect;
			bool filter_clip;
			_get_rects(src_rect, dst_rect, filter_clip);
			texture->draw_rect_region(ci, dst_rect, src_rect, Color(1, 1, 1), false, normal_map, filter_clip);
		} break;

		case NOTIFICATION_PROCESS:
		{
			location(getMouseLocation());
			update();
		}
	}
}

void MouseImageNode::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const {

	Rect2 base_rect;

	if (region) {
		r_filter_clip = region_filter_clip;
		base_rect = region_rect;
	} else {
		r_filter_clip = false;
		base_rect = Rect2(0, 0, texture->get_width(), texture->get_height());
	}

	Size2 frame_size = base_rect.size / Size2(hframes, vframes);
	Point2 frame_offset = Point2(frame % hframes, frame / hframes);
	frame_offset *= frame_size;

	r_src_rect.size = frame_size;
	r_src_rect.position = base_rect.position + frame_offset;

	Point2 dest_offset = offset;
	if (centered)
		dest_offset -= frame_size / 2;
	if (Engine::get_singleton()->get_use_pixel_snap()) {
		dest_offset = dest_offset.floor();
	}

	r_dst_rect = Rect2(dest_offset, frame_size);
}

void MouseImageNode::set_texture(const Ref<Texture> &p_texture)
{
	if (p_texture == texture)
		return;

	if (texture.is_valid())
		texture->disconnect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");

	texture = p_texture;

	if (texture.is_valid())
		texture->connect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");

	update();
	item_rect_changed();
	_change_notify("texture");
}

void MouseImageNode::_texture_changed()
{
	if (texture.is_valid())
	{
		update();
	}
}

Ref<Texture> MouseImageNode::get_texture() const {

	return texture;
}

void MouseImageNode::set_offset(const Point2 &p_offset) {

	offset = p_offset;
	update();
	item_rect_changed();
	_change_notify("offset");
}
Point2 MouseImageNode::get_offset() const {

	return offset;
}
