//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/main/node.h"

class Entity : public Node {
	GDCLASS(Entity, Node);

protected:
  static void _bind_methods();

  // Integers
  int ID;

public:
  Entity();

  // Setter Functions
  void setID(int newID);

  // Getter Functions
  int getID();
};

#endif
