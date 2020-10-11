//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/2d/node_2d.h"
#include "core/core_string_names.h"

class Entity : public Node2D {
	GDCLASS(Entity, Node2D);

protected:
  static void _bind_methods();

  // Integers
  int ID;

    void _notification(int p_what);
  virtual void _validate_property(PropertyInfo &property) const {};

  // Strings
  String imagePath;

  // RID's
  RID canvas;

  // Textures
  Ref<Texture> texture;
  Ref<Texture> normal_map;

  // Point2's
  Point2 offset;

public:
  Entity();
  void setPosition(Vector2 newPos);
  Vector2 getPosition();
  bool CheckForOverlap();

  Vector2 GetScale();
  void SetScale(Vector2 newScale);
  void SetCollisionShape(String newShape);

  // Path functions
  void path(const String &a);
};

#endif
