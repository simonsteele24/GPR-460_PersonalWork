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
	EntityManager::GetInstance()->SetOffset(EntityManager::GetInstance()->GetPosition(ID), ID);
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
	EntityManager::GetInstance()->SetPath(a, ID);
}

void Entity::_notification(int p_what) {
	switch (p_what) {

		// Draw
		case NOTIFICATION_DRAW: {

			// Draw mouse image if texture is valid
			RID ci = get_canvas_item();
			EntityManager::GetInstance()->DrawTexture(ci, ID);
		} break;

		// Update
		case NOTIFICATION_PROCESS: {
			update();
		}
	}
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
