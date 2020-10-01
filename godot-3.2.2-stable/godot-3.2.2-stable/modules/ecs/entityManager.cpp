#include "entityManager.h"

EntityManager::EntityManager(){}

//Bind all your methods used in this class
void EntityManager::_bind_methods(){
  ClassDB::bind_method(D_METHOD("generateID"), &EntityManager::generateID);
}


//Custom Functions
int EntityManager::generateID()
{
	numOFEntities++;
	return numOFEntities;
}

