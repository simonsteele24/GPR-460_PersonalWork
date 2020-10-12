#include "collisionhull.h"

// This is the default constructor of the class
CollisionHull::CollisionHull()
{
	shapeType = Circle;
}



// This function sets the shape type of the collision component based on a given shape
void CollisionHull::setHullType(const Shapes &newShape)
{
	shapeType = newShape;
}



// This function gets the shape type of the collision component
Shapes CollisionHull::getHullType() const
{
	return shapeType;
}



// This function sets the radius of the collision component based on a given radius
void CollisionHull::changeRadius(const float &newRadius)
{
	if (shapeType == Circle)
	{
		radius = newRadius;
	}
}



// This function gets the radius of the collision component
int CollisionHull::getRadius() const
{
	if (shapeType != Circle)
	{
		return 0;
	}
	return radius;
}



// This function sets the half lengths of the collision component based on given half lengths
void CollisionHull::changeHalfLengths(const float &newHalfLengthX, const float &newHalfLengthY)
{
	if (shapeType == Rectangle)
	{
		halfLengthX = newHalfLengthX;
		halfLengthY = newHalfLengthY;
	}
}



// This function gets the half lengths of the collision component
Vector2 CollisionHull::getHalfLength()
{
	return Vector2(halfLengthX, halfLengthY);
}



// This function gets the max corner of the collision component based on a given position
Vector2 CollisionHull::getMaxCorner(const Vector2 &position)
{
	return Vector2(position.x + halfLengthX, position.y + halfLengthY);
}



// This function gets the min corner of the collision component based on a given position
Vector2 CollisionHull::getMinCorner(const Vector2 &position)
{
	return Vector2(position.x - halfLengthX, position.y - halfLengthY);
}
