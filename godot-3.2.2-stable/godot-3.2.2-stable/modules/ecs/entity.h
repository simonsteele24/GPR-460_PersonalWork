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

  void setupNewTexture();

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

  // Texture functions
  void _texture_changed();
  void set_texture(const Ref<Texture> &p_texture);
  Ref<Texture> get_texture() const;

  // Rect functions
  void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const;

  // Offset functions
  void set_offset(const Point2 &p_offset);
  Point2 get_offset() const;
};

#endif
