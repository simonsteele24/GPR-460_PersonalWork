//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/main/node.h"

using namespace std;

class MouseImageNode : public Node {
	GDCLASS(MouseImageNode, Node);

protected:
  static void _bind_methods();

public:
  MouseImageNode();

  String add(String a);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);

};

#endif
