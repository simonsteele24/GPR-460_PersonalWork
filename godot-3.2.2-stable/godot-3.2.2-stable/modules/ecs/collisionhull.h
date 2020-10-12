//insert the Headername here
#ifndef COLLISIONHULL_H
#define COLLISIONHULL_H

#include <iostream>
#include <vector>
#include "scene/2d/node_2d.h"

using namespace std;

enum Shapes
{
	Circle,
	Rectangle
};

class CollisionHull {

protected:
	// Floats
	float halfLengthX;
	float halfLengthY;
	float radius;

	// Shape types
	Shapes shapeType;

public:
  CollisionHull();

  // Setters
  void setHullType(const Shapes &newShape);
  void changeRadius(const float &newRadius);
  void changeHalfLengths(const float &newHalfLengthX, const float &newHalfLengthY);

  // Getters
  Shapes getHullType() const;
  Vector2 getHalfLength();
  int getRadius() const;
  Vector2 getMinCorner(const Vector2 &position);
  Vector2 getMaxCorner(const Vector2 &position);
};

#endif
