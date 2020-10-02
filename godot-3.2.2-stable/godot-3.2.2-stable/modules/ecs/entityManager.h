//insert the Headername here
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "scene/main/node.h"
#include <iostream>
using namespace std;

class EntityManager
{
	

protected:

  int numOFEntities = -1;
  Vector<Vector2> positions;

public:
	static EntityManager* instance;
  EntityManager();

  static EntityManager* GetInstance()
  {
	  if (!instance)
	  {
		  instance = new EntityManager;
	  }
	  return instance;
  }

  int generateID();
  Vector2 GetPosition(int ID);
  void SetPosition(int ID, Vector2 newPos);

};

#endif
