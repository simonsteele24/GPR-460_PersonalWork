//insert the Headername here
#ifndef COMPONENT_H
#define COMPONENT_H

#include "scene/main/node.h"

class Component : public Node {
	GDCLASS(Component, Node);

protected:
  static void _bind_methods();

public:
  Component();

  int add(int a, int b);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);

};

#endif
