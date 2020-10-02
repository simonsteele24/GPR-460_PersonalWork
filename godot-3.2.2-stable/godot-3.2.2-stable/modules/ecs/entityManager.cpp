#include "entityManager.h"
EntityManager* EntityManager::instance = 0;

EntityManager::EntityManager()
{
	positions = Vector<Vector2>();
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
