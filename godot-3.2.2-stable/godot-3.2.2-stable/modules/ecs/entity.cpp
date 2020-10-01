#include "entity.h"

Entity::Entity(){}

//Bind all your methods used in this class
void Entity::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("setID", "new ID"), &Entity::setID);
  ClassDB::bind_method(D_METHOD("getID"), &Entity::getID);
}

void Entity::setID(int newID)
{
	ID = newID;
}

int Entity::getID()
{
	return ID;
}
