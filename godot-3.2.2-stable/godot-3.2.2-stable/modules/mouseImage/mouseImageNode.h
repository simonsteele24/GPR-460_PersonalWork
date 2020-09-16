//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/main/node.h"
#include "scene/2d/canvas_item.h"
#include "core/os/input.h"

using namespace std;

class MouseImageNode : public Node {
	GDCLASS(MouseImageNode, Node);

protected:
  static void _bind_methods();

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
