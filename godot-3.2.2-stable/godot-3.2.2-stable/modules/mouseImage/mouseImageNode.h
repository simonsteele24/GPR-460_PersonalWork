//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/main/node.h"

using namespace std;

class MouseImageNode : public Node {
	GDCLASS(MouseImageNode, Node);

protected:
  static void _bind_methods();

  int iconLocationX;
  int iconLocationY;
  String imagePath;

public:
  MouseImageNode();

  void path(String a);
  void location(int a, int b);
  void draw();

};

#endif
