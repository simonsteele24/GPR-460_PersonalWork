//insert the Headername here
#ifndef CATMULLCLARKNODE_H
#define CATMULLCLARKNODE_H

#include "scene/main/node.h"

class CatmullClarkNode : public Node {
	GDCLASS(CatmullClarkNode, Node);

protected:
  static void _bind_methods();

public:
	CatmullClarkNode();

  int add(int a, int b);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);

};

#endif
