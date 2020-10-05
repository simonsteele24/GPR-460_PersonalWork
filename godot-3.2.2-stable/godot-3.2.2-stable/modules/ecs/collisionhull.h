//insert the Headername here
#ifndef COLLISIONHULL_H
#define COLLISIONHULL_H

#include <iostream>
#include "scene/2d/node_2d.h"

using namespace std;

enum Shapes
{
	Circle,
	Rectangle
};


class CollisionHull {

protected:
	int halfLengthX;
	int halfLengthY;
	int radius;

	Shapes shapeType;

public:
  CollisionHull();

  void SetHullType(Shapes newShape);
  Shapes GetHullType();
  void ChangeRadius(int newRadius);
  void ChangeHalfLengths(int newHalfLengthX,int newHalfLengthY);
  Vector2 GetHalfLength();
  int GetRadius();
  Vector2 GetMinCorner(Vector2 position);
  Vector2 GetMaxCorner(Vector2 position);
};

#endif
