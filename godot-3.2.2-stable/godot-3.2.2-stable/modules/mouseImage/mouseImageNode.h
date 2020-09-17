//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/2d/node_2d.h"
#include "scene/2d/canvas_item.h"
#include "core/os/input.h"

using namespace std;

class MouseImageNode : public Node2D {
	GDCLASS(MouseImageNode, Node2D);

protected:
  static void _bind_methods();
  void _notification(int p_what){};
  virtual void _validate_property(PropertyInfo &property) const {};
  int iconLocationX;
  int iconLocationY;
  String imagePath;
  RID canvas;
  RID texture;

public:
  MouseImageNode();

  void path(String a);
  void location(int a, int b);
  Point2 getMouseLocation();
  void draw();

};

#endif
