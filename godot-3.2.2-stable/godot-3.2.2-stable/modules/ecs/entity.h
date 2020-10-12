#ifndef ENTITY_H
#define ENTITY_H

#include "scene/2d/node_2d.h"
#include "core/core_string_names.h"

class Entity : public Node2D {
	GDCLASS(Entity, Node2D);

protected:

  // Integers
  int ID;

  // Node 2D Functions
  void _notification(int p_what);
  virtual void _validate_property(PropertyInfo &property) const {};
  static void _bind_methods();

public:

  Entity();

  // Setters
  void setPosition(const Vector2 &newPos);
  void setScale(const Vector2 &newScale);
  void setCollisionShape(const String &newShape);

  // Getters
  Vector2 getPosition();
  bool checkForOverlap();
  Vector2 getScale();
  

  // Path functions
  void path(const String &a);
};

#endif
