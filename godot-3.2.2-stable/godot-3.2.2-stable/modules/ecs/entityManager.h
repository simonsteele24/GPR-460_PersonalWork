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

  // Integers
  int numOFEntities = -1;

  // vectors
  vector<Vector2> positions;
  vector<Vector2> scales;
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

  // Getters
  int generateID();
  Vector2 getPosition(const int &ID);
  Vector2 getScale(const int &ID);
  Shapes getShape(const int &ID);
  Point2 getOffset(const int &ID) const;

  // Setters
  void setPosition(const int &ID, const Vector2 &newPos);
  void setScale(const int &ID, const Vector2 &newScale);
  void setShape(const int &ID, const Shapes &newShape);
  void setBounds(const int &ID, const Vector2 &newBounds);
  void setPath(const String &newPath, const int &ID);
  void setOffset(const Point2 &newOffset, const int &ID);

  // Update/draw functions
  bool rectangleCircleCollision(const int &circleID, const int &rectangleID);
  bool checkForOverlap(const int &cicleID);
  void drawTexture(const RID &canvas, const int &ID);

};

#endif
