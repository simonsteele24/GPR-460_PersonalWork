#include "entity.h"
#include "entityManager.h"

Entity::Entity()
{
	ID = EntityManager::GetInstance()->generateID();
}

//Bind all your methods used in this class
void Entity::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("setPosition", "newPos"), &Entity::setPosition);
	ClassDB::bind_method(D_METHOD("getPosition"), &Entity::setPosition);
}

void Entity::setPosition(Vector2 newPos)
{
	EntityManager::GetInstance()->SetPosition(ID, newPos);
}

Vector2 Entity::getPosition()
{
	return EntityManager::GetInstance()->GetPosition(ID);
}
