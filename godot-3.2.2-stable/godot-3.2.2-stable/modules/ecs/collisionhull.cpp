#include "collisionhull.h"

CollisionHull::CollisionHull(){}

void CollisionHull::SetHullType(Shapes newShape)
{
	shapeType = newShape;
}

Shapes CollisionHull::GetHullType()
{
	return shapeType;
}

void CollisionHull::ChangeRadius(int newRadius)
{
	if (shapeType == Circle)
	{
		radius = newRadius;
	}
}

int CollisionHull::GetRadius()
{
	return radius;
}

void CollisionHull::ChangeHalfLengths(int newHalfLengthX, int newHalfLengthY)
{
	if (shapeType == Rectangle)
	{
		halfLengthX = newHalfLengthX;
		halfLengthY = newHalfLengthY;
	}
}

Vector2 CollisionHull::GetHalfLength()
{
	return Vector2(halfLengthX, halfLengthY);
}

Vector2 CollisionHull::GetMaxCorner(Vector2 position)
{
	return Vector2(position.x + halfLengthX, position.y + halfLengthY);
}

Vector2 CollisionHull::GetMinCorner(Vector2 position)
{
	return Vector2(position.x - halfLengthX, position.y - halfLengthY);
}
