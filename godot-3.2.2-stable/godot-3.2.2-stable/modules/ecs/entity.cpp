#include "entity.h"
#include "entityManager.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"



// This is the default constructor for this class
Entity::Entity()
{
	ID = EntityManager::GetInstance()->generateID();
}



//Bind all your methods used in this class
void Entity::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("setPosition", "newPos"), &Entity::setPosition);
	ClassDB::bind_method(D_METHOD("getPosition"), &Entity::getPosition);
	ClassDB::bind_method(D_METHOD("checkForOverlap"), &Entity::checkForOverlap);
	ClassDB::bind_method(D_METHOD("setScale", "newScale"), &Entity::setScale);
	ClassDB::bind_method(D_METHOD("getScale"), &Entity::getScale);
	ClassDB::bind_method(D_METHOD("setShape", "newShape"), &Entity::setCollisionShape);
	ClassDB::bind_method(D_METHOD("path", "newPath"), &Entity::path);
}



// This function sets the position of the entity by a given position
void Entity::setPosition(const Vector2 &newPos)
{
	EntityManager::GetInstance()->setPosition(ID, newPos);
	EntityManager::GetInstance()->setOffset(EntityManager::GetInstance()->getPosition(ID), ID);
}



// This function gets the position of the entity
Vector2 Entity::getPosition()
{
	return EntityManager::GetInstance()->getPosition(ID);
}



// This function gets the scale of the entity
Vector2 Entity::getScale()
{
	return EntityManager::GetInstance()->getScale(ID);
}



// This function sets the scale of the entity by a given value
void Entity::setScale(const Vector2 &newScale)
{
	EntityManager::GetInstance()->setScale(ID, newScale);
	EntityManager::GetInstance()->setBounds(ID, newScale);
}



// This function sets the texture of the entity based on a given path
void Entity::path(const String &a) {
	EntityManager::GetInstance()->setPath(a, ID);
}



// This is where all update/draw functions go
void Entity::_notification(int p_what) {
	switch (p_what) {

		// Draw
		case NOTIFICATION_DRAW: {

			// Draw mouse image if texture is valid
			RID ci = get_canvas_item();
			EntityManager::GetInstance()->drawTexture(ci, ID);
		} break;

		// Update
		case NOTIFICATION_PROCESS: {
			update();
		}
	}
}



// This function checks if any entities are colliding with this one
bool Entity::checkForOverlap()
{
	return EntityManager::GetInstance()->checkForOverlap(ID);
}



// This function sets the collision hull type of the entity
void Entity::setCollisionShape(const String &newShape)
{
	if (newShape == "Circle")
	{
		EntityManager::GetInstance()->setShape(ID, Circle);
	}
	else
	{
		EntityManager::GetInstance()->setShape(ID, Rectangle);
	}
}
