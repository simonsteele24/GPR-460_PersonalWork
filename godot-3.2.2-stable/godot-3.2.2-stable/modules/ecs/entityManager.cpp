#include "entityManager.h"
EntityManager *EntityManager::instance = 0;



// This is the default constructor of the class
EntityManager::EntityManager() {
	positions = vector<Vector2>();
}



// This function generates the ID and components of the Entity
int EntityManager::generateID() {
	numOFEntities++;
	positions.push_back(Vector2(0, 0));
	collisions.push_back(CollisionHull());
	textures.push_back(TextureComponent());
	scales.push_back(Vector2(1, 1));
	return numOFEntities;
}



// This function gets the position from the component
Vector2 EntityManager::getPosition(const int &ID){
	return positions[ID];
}



// This function sets the position of the component of a given ID and new position
void EntityManager::setPosition(const int &ID, const Vector2 &newPos) {
	positions[ID] = newPos;
}



// This function sets the scale of the component of a given ID and new scale
void EntityManager::setScale(const int &ID, const Vector2 &newScale)
{
	scales[ID] = newScale;
}



// This function gets the scale from the component
Vector2 EntityManager::getScale(const int &ID){
	return scales[ID];
}



// This function checks if a circle and rectangle hulls collide based on their given IDs
bool EntityManager::rectangleCircleCollision(const int &circleID, const int &rectangleID) {
	Vector2 closestPointToCircle = Vector2(max(collisions[rectangleID].getMinCorner(getPosition(rectangleID)).x, min(getPosition(circleID).x, collisions[rectangleID].getMaxCorner(getPosition(rectangleID)).x)), max(collisions[rectangleID].getMinCorner(getPosition(rectangleID)).y, min(getPosition(circleID).y, collisions[rectangleID].getMaxCorner(getPosition(rectangleID)).y)));

	Vector2 distance = getPosition(circleID) - closestPointToCircle;

	bool axisCheck = distance.dot(distance) <= collisions[circleID].getRadius() * collisions[circleID].getRadius();

	return axisCheck;
}



// This function checks if an entity collides with an other entities based on a given ID
bool EntityManager::checkForOverlap(const int &circleID) {
	bool isOverlapped = false;
	int size = collisions.size();
	for (int i = 0; i < size; i++) {
		if (collisions[i].getHullType() != Circle && i != circleID && isOverlapped == false) {
			isOverlapped = rectangleCircleCollision(circleID, i);
		}
	}
	return isOverlapped;
}



// This function gets the collision hull type from the ID
Shapes EntityManager::getShape(const int &ID)
{
	Shapes newShape = collisions[ID].getHullType();
	return newShape;
}



// This function sets the collision hull type from the ID and the new type
void EntityManager::setShape(const int &ID, const Shapes &newShape)
{
	collisions[ID].setHullType(newShape);
}



// This function sets the boundaries of the collision hull based on the ID and new bounds
void EntityManager::setBounds(const int &ID, const Vector2 &newBounds)
{
	if (collisions[ID].getHullType() == Circle)
	{
		collisions[ID].changeRadius(newBounds.x * 100);
	}
	else
	{
		collisions[ID].changeHalfLengths(newBounds.x * 100, newBounds.y * 100);
	}
}



// This function sets the texture component via path based on the given path and ID
void EntityManager::setPath(const String &newPath, const int &ID)
{
	textures[ID].path(newPath);
}



// This function draws the texture onto the canvas item (the entity) based on the given RID and ID
void EntityManager::drawTexture(const RID &canvas, const int &ID)
{
	textures[ID].draw(canvas, ID);
}



// This function sets the offset of the texture based on the given offset and ID
void EntityManager::setOffset(const Point2 &newOffset, const int &ID)
{
	textures[ID].set_offset(newOffset);
}



// This function gets the offset of the texture component
Point2 EntityManager::getOffset(const int &ID) const
{
	return textures[ID].get_offset();
}
