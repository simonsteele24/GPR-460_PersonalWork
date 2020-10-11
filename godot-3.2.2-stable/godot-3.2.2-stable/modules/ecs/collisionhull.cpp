#include "collisionhull.h"

CollisionHull::CollisionHull()
{
	shapeType = Circle;
}

void CollisionHull::SetHullType(Shapes newShape)
{
	shapeType = newShape;
}

Shapes CollisionHull::GetHullType()
{
	return shapeType;
}

void CollisionHull::ChangeRadius(float newRadius)
{
	if (shapeType == Circle)
	{
		radius = newRadius;
	}
}

int CollisionHull::GetRadius()
{
	if (shapeType != Circle)
	{
		return 0;
	}
	return radius;
}

void CollisionHull::ChangeHalfLengths(float newHalfLengthX, float newHalfLengthY)
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
