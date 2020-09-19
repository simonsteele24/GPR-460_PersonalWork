#include "mouseImageNode.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"

// This function is the default constructor for this class
MouseImageNode::MouseImageNode()
{
	canvas = VisualServer::get_singleton()->canvas_item_create();
}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("path", "a"), &MouseImageNode::path);
}


// This function sets the image path for the mouse image based on the path string
void MouseImageNode::path(const String &a) {
	imagePath = a;
	setupNewTexture();
}


// This function returns the location of the mouse cursor in screen space
Point2 MouseImageNode::getMouseLocation() const
{
	return OS::get_singleton()->get_mouse_position();
}


// This function sets up the new image icon based on the image path presented earlier
void MouseImageNode::setupNewTexture()
{
	if (imagePath != "")
	{
		Ref<Image> img;
		img.instance();
		img->load(imagePath);
		Ref<ImageTexture> newTex;
		newTex.instance();
		newTex->create_from_image(img);
		set_texture(newTex);
	}
	
}


// This function updates the location of the mouse icon based on the location of the mouse cursor
void MouseImageNode::updateLocation()
{
	set_offset(getMouseLocation());
}


// This function gets triggered whenever a notification is recieved
void MouseImageNode::_notification(int p_what)
{
	switch (p_what) {

		// Draw
		case NOTIFICATION_DRAW: {

			// Draw mouse image if texture is valid
			if (texture.is_null())
				return;
			RID ci = get_canvas_item();
			Rect2 src_rect, dst_rect;
			bool filter_clip;
			_get_rects(src_rect, dst_rect, filter_clip);
			texture->draw_rect_region(ci, dst_rect, src_rect, Color(1, 1, 1), false, normal_map, filter_clip);
		} break;

		// Update
		case NOTIFICATION_PROCESS:
		{
			updateLocation();
			update();
		}
	}
}


// This function gets and sets all of the rectangular regions for drawing
void MouseImageNode::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const {

	Rect2 base_rect;

	r_filter_clip = false;
	base_rect = Rect2(0, 0, texture->get_width(), texture->get_height());

	Size2 frame_size = base_rect.size;
	Point2 frame_offset = Point2(1, 1);
	frame_offset *= frame_size;

	r_src_rect.size = frame_size;
	r_src_rect.position = base_rect.position + frame_offset;

	Point2 dest_offset = offset;
	dest_offset -= frame_size / 2;

	if (Engine::get_singleton()->get_use_pixel_snap()) {
		dest_offset = dest_offset.floor();
	}

	r_dst_rect = Rect2(dest_offset, frame_size);
}


// This function sets the texture of the icon and notifies the visual server that it has been changed
void MouseImageNode::set_texture(const Ref<Texture> &p_texture)
{
	if (p_texture == texture)
		return;

	if (texture.is_valid())
		texture->disconnect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");

	texture = p_texture;

	if (texture.is_valid())
		texture->connect(CoreStringNames::get_singleton()->changed, this, "_texture_changed");

	item_rect_changed();
	_change_notify("texture");
}


// This function is triggered whenever the texture is changed
void MouseImageNode::_texture_changed()
{
	if (texture.is_valid())
	{
		update();
	}
}


// This function gets the current texture of the icon
Ref<Texture> MouseImageNode::get_texture() const {

	return texture;
}


// This function sets the offset of the cursor image
void MouseImageNode::set_offset(const Point2 &p_offset) {

	offset = p_offset;
	update();
	item_rect_changed();
	_change_notify("offset");
}


// This function gets the offset of the cursor image
Point2 MouseImageNode::get_offset() const {

	return offset;
}
