//insert the Headername here
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "scene/main/node.h"
#include <iostream>
#include <algorithm>
#include "collisionhull.h"
using namespace std;

class EntityManager
{
	

protected:

  int numOFEntities = -1;
  Vector<Vector2> positions;
  Vector<Vector2> scales;
  Vector<CollisionHull> collisions;

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
  Vector2 GetScale(int ID);
  void SetPosition(int ID, Vector2 newPos);
  void SetScale(int ID, Vector2 newScale);
  Shapes GetShape(int ID);
  void SetShape(int ID, Shapes newShape);
  bool RectangleCircleCollision(int circleID, int rectangleID);
  bool CheckForOverlap(int cicleID);

};

#endif
