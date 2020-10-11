#include "textureComponent.h"
#include "entityManager.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"

void TextureComponent::setupNewTexture()
{
	if (imagePath != "") {
		Ref<Image> img;
		img.instance();
		img->load(imagePath);
		Ref<ImageTexture> newTex;
		newTex.instance();
		newTex->create_from_image(img);
		set_texture(newTex);
	}
}

void TextureComponent::path(const String &a)
{
	imagePath = a;
	setupNewTexture();
}

void TextureComponent::set_texture(const Ref<Texture> &p_texture) {
	if (p_texture == texture)
		return;

	texture = p_texture;
}

// This function gets the current texture of the icon
Ref<Texture> TextureComponent::get_texture() const
{

	return texture;
}

void TextureComponent::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip, int ID) const {

	Rect2 base_rect;

	r_filter_clip = false;
	base_rect = Rect2(0, 0, texture->get_width(), texture->get_height());

	Size2 frame_size = base_rect.size;
	Point2 frame_offset = Point2(1, 1);
	frame_offset *= frame_size;

	r_src_rect.size = frame_size;
	r_src_rect.position = base_rect.position + frame_offset;

	Point2 dest_offset = offset;
	dest_offset -= (frame_size * EntityManager::GetInstance()->GetScale(ID)) / 2;

	if (Engine::get_singleton()->get_use_pixel_snap()) {
		dest_offset = dest_offset.floor();
	}

	r_dst_rect = Rect2(dest_offset, frame_size * EntityManager::GetInstance()->GetScale(ID));
}

void TextureComponent::set_offset(const Point2 &p_offset)
{
	offset = p_offset;
}

Point2 TextureComponent::get_offset() const {

	return offset;
}

void TextureComponent::draw(const RID &canvas, const int &ID)
{
	if (texture.is_null())
	{
		return;
	}
	Rect2 src_rect, dst_rect;
	bool filter_clip;
	_get_rects(src_rect, dst_rect, filter_clip, ID);
	texture->draw_rect_region(canvas, dst_rect, src_rect, Color(1, 1, 1), false, normal_map, filter_clip);
}
