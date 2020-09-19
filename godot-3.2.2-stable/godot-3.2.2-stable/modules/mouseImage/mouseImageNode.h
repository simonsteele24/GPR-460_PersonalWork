//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/2d/node_2d.h"
#include "scene/2d/canvas_item.h"
#include "core/os/input.h"
#include "core/core_string_names.h"

using namespace std;

class MouseImageNode : public Node2D {
	GDCLASS(MouseImageNode, Node2D);

protected:
  // Update input functions
  Point2 getMouseLocation();
  void updateLocation();

  // Private Texture Functions
  void setupNewTexture();

  // Built-in Node2D functions
  static void _bind_methods();
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

  // Constructor / Destructors
  MouseImageNode();
  ~MouseImageNode(){};

  // Path functions
  void path(String a);

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
