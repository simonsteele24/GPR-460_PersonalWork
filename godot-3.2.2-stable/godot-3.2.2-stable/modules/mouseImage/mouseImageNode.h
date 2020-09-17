//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/2d/node_2d.h"
#include "scene/2d/canvas_item.h"
#include "core/os/input.h"
#include "core/core_string_names.h"
#include "core/print_string.h"

using namespace std;

class MouseImageNode : public Node2D {
	GDCLASS(MouseImageNode, Node2D);

protected:
  static void _bind_methods();
  void _notification(int p_what);
  virtual void _validate_property(PropertyInfo &property) const {};
  int iconLocationX;
  int iconLocationY;
  String imagePath;
  RID canvas;
  bool region;
  int frame;
  Ref<Texture> texture;
  Ref<Texture> normal_map;
  bool centered;
  Point2 offset;
  Rect2 region_rect;
  bool region_filter_clip;
  int vframes;
  int hframes;
public:
  MouseImageNode();

  void path(String a);
  void location(Point2 newLocation);
  Point2 getMouseLocation();
  void draw();
  void _texture_changed();
  void set_texture(const Ref<Texture> &p_texture);
  Ref<Texture> get_texture() const;
  void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip) const;
  void set_offset(const Point2 &p_offset);
  Point2 get_offset() const;

};

#endif
