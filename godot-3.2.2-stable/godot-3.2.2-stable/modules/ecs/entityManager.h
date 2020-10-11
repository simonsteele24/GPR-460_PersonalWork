//insert the Headername here
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "scene/main/node.h"
#include <iostream>
#include <algorithm>
#include "collisionhull.h"
#include "textureComponent.h"
using namespace std;

class EntityManager
{
	

protected:

  int numOFEntities = -1;
  Vector<Vector2> positions;
  Vector<Vector2> scales;
  vector<CollisionHull> collisions;
  vector<TextureComponent> textures;

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
  void SetBounds(int ID, Vector2 newBounds);
  bool RectangleCircleCollision(int circleID, int rectangleID);
  bool CheckForOverlap(int cicleID);
  void SetPath(String newPath, int ID);
  void DrawTexture(RID canvas, int ID);
  void SetOffset(Point2 newOffset, int ID);
  Point2 GetOffset(int ID);

};

#endif
