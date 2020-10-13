//insert the Headername here
#ifndef CATMULLCLARKREF_H
#define CATMULLCLARKREF_H

#include "core/reference.h"

class CatmullClarkRef : public Reference {
  GDCLASS(CatmullClarkRef, Reference);

protected:
  static void _bind_methods();

public:
  CatmullClarkRef();

  int add(int a, int b);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);

};

#endif
