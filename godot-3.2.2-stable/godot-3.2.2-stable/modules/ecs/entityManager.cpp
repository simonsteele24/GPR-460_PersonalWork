#include "entityManager.h"
EntityManager *EntityManager::instance = 0;

EntityManager::EntityManager() {
	positions = Vector<Vector2>();
}

//Custom Functions
int EntityManager::generateID() {
	numOFEntities++;
	positions.push_back(Vector2(0, 0));
	collisions.push_back(CollisionHull());
	scales.push_back(Vector2(1, 1));
	return numOFEntities;
}

Vector2 EntityManager::GetPosition(int ID) {
	return positions.get(ID);
}

void EntityManager::SetPosition(int ID, Vector2 newPos) {
	positions.set(ID, newPos);
}

void EntityManager::SetScale(int ID, Vector2 newScale) {
	scales.set(ID, newScale);
}

Vector2 EntityManager::GetScale(int ID) {
	return Vector2(collisions.get(ID).GetRadius(), collisions.get(ID).GetRadius());
}

bool EntityManager::RectangleCircleCollision(int circleID, int rectangleID) {
	Vector2 closestPointToCircle = Vector2(max(collisions.get(rectangleID).GetMinCorner(GetPosition(rectangleID)).x, min(GetPosition(circleID).x, collisions.get(rectangleID).GetMaxCorner(GetPosition(rectangleID)).x)), max(collisions.get(rectangleID).GetMinCorner(GetPosition(rectangleID)).y, min(GetPosition(circleID).y, collisions.get(rectangleID).GetMaxCorner(GetPosition(rectangleID)).y)));

	Vector2 distance = GetPosition(circleID) - closestPointToCircle;

	bool axisCheck = distance.dot(distance) <= collisions.get(circleID).GetRadius() * collisions.get(circleID).GetRadius();

	return axisCheck;
}

bool EntityManager::CheckForOverlap(int circleID) {
	bool isOverlapped = false;
	int size = collisions.size();
	for (int i = 0; i < size; i++) {
		if (collisions.get(i).GetHullType() != Circle && i != circleID && isOverlapped == false) {
			isOverlapped = RectangleCircleCollision(circleID, i);
		}
	}
	return isOverlapped;
}


Shapes EntityManager::GetShape(int ID)
{
	return collisions.get(ID).GetHullType();
}


void EntityManager::SetShape(int ID, Shapes newShape)
{
	collisions.get(ID).SetHullType(newShape);
}



void EntityManager::SetBounds(int ID, Vector2 newBounds)
{
	if (collisions.get(ID).GetHullType() == Circle)
	{
		collisions.get(ID).ChangeRadius(newBounds.x * 10);
	}
	else
	{
		collisions.get(ID).ChangeHalfLengths(newBounds.x * 10, newBounds.y * 10);
	}
}
