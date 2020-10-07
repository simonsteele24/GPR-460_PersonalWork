#include "entity.h"
#include "entityManager.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"

Entity::Entity()
{
	ID = EntityManager::GetInstance()->generateID();
}

//Bind all your methods used in this class
void Entity::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("setPosition", "newPos"), &Entity::setPosition);
	ClassDB::bind_method(D_METHOD("getPosition"), &Entity::getPosition);
	ClassDB::bind_method(D_METHOD("checkForOverlap"), &Entity::CheckForOverlap);
	ClassDB::bind_method(D_METHOD("setScale", "newScale"), &Entity::SetScale);
	ClassDB::bind_method(D_METHOD("getScale"), &Entity::GetScale);
	ClassDB::bind_method(D_METHOD("setShape", "newShape"), &Entity::SetCollisionShape);
	ClassDB::bind_method(D_METHOD("path", "newPath"), &Entity::path);
}

void Entity::setPosition(Vector2 newPos)
{
	EntityManager::GetInstance()->SetPosition(ID, newPos);
	set_offset(EntityManager::GetInstance()->GetPosition(ID));
}

Vector2 Entity::getPosition()
{
	return EntityManager::GetInstance()->GetPosition(ID);
}

Vector2 Entity::GetScale()
{
	return EntityManager::GetInstance()->GetScale(ID);
}

void Entity::SetScale(Vector2 newScale)
{
	EntityManager::GetInstance()->SetScale(ID, newScale);
	EntityManager::GetInstance()->SetBounds(ID, newScale);
}

void Entity::path(const String &a) {
	imagePath = a;
	setupNewTexture();
}

void Entity::setupNewTexture() {
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

void Entity::_notification(int p_what) {
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
		case NOTIFICATION_PROCESS: {
			update();
		}
	}
}

void Entity::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const {

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

void Entity::set_texture(const Ref<Texture> &p_texture) {
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

void Entity::_texture_changed() {
	if (texture.is_valid()) {
		update();
	}
}

// This function gets the current texture of the icon
Ref<Texture> Entity::get_texture() const {

	return texture;
}

// This function sets the offset of the cursor image
void Entity::set_offset(const Point2 &p_offset) {

	offset = p_offset;
	update();
	item_rect_changed();
	_change_notify("offset");
}

// This function gets the offset of the cursor image
Point2 Entity::get_offset() const {

	return offset;
}

bool Entity::CheckForOverlap()
{
	return EntityManager::GetInstance()->CheckForOverlap(ID);
}

void Entity::SetCollisionShape(String newShape)
{
	if (newShape == "Circle")
	{
		EntityManager::GetInstance()->SetShape(ID, Circle);
	}
	else
	{
		EntityManager::GetInstance()->SetShape(ID, Rectangle);
	}
}
