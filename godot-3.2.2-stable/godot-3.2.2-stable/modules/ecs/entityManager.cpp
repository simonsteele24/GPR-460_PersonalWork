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

void EntityManager::SetScale(int ID, Vector2 newScale)
{
	scales.set(ID, newScale);
}

Vector2 EntityManager::GetScale(int ID) {
	return scales.get(ID);
}

bool EntityManager::RectangleCircleCollision(int circleID, int rectangleID) {
	Vector2 closestPointToCircle = Vector2(max(collisions[rectangleID].GetMinCorner(GetPosition(rectangleID)).x, min(GetPosition(circleID).x, collisions[rectangleID].GetMaxCorner(GetPosition(rectangleID)).x)), max(collisions[rectangleID].GetMinCorner(GetPosition(rectangleID)).y, min(GetPosition(circleID).y, collisions[rectangleID].GetMaxCorner(GetPosition(rectangleID)).y)));

	Vector2 distance = GetPosition(circleID) - closestPointToCircle;

	bool axisCheck = distance.dot(distance) <= collisions[circleID].GetRadius() * collisions[circleID].GetRadius();

	return axisCheck;
}

bool EntityManager::CheckForOverlap(int circleID) {
	bool isOverlapped = false;
	int size = collisions.size();
	for (int i = 0; i < size; i++) {
		if (collisions[i].GetHullType() != Circle && i != circleID && isOverlapped == false) {
			isOverlapped = RectangleCircleCollision(circleID, i);
		}
	}
	return isOverlapped;
}


Shapes EntityManager::GetShape(int ID)
{
	return collisions[ID].GetHullType();
}


void EntityManager::SetShape(int ID, Shapes newShape)
{
	collisions[ID].SetHullType(newShape);
}



void EntityManager::SetBounds(int ID, Vector2 newBounds)
{
	if (collisions[ID].GetHullType() == Circle)
	{
		collisions[ID].ChangeRadius(newBounds.x * 100);
	}
	else
	{
		collisions[ID].ChangeHalfLengths(newBounds.x * 100, newBounds.y * 100);
	}
}
