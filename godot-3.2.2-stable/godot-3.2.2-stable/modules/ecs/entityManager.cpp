#include "entityManager.h"

EntityManager::EntityManager()
{
	positions = Vector<Vector2>();
}

//Bind all your methods used in this class
void EntityManager::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("generateID"), &EntityManager::generateID);
  ClassDB::bind_method(D_METHOD("getPosition", "ID"), &EntityManager::GetPosition);
  ClassDB::bind_method(D_METHOD("setPosition", "ID", "New Position"), &EntityManager::SetPosition);
}


//Custom Functions
int EntityManager::generateID()
{
	numOFEntities++;
	positions.push_back(Vector2(0,0));
	return numOFEntities;
}

Vector2 EntityManager::GetPosition(int ID)
{
	return positions.get(ID);
}


void EntityManager::SetPosition(int ID, Vector2 newPos)
{
	positions.set(ID, newPos);
}
