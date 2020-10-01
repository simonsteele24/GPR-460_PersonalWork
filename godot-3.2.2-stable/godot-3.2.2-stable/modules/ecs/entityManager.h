//insert the Headername here
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "scene/main/node.h"

class EntityManager : public Node {
  GDCLASS(EntityManager, Node);

protected:
  static void _bind_methods();

  int numOFEntities = -1;

public:
  EntityManager();

  int generateID();

};

#endif
