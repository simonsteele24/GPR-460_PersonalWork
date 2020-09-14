//insert the Headername here
#ifndef CALCULATORREF_H
#define CALCULATORREF_H

#include "core/reference.h"

using namespace std;

class MouseImageRef : public Reference {
  GDCLASS(MouseImageRef, Reference);

protected:
  static void _bind_methods();

public:
  MouseImageRef();

 void path(String a);
  void location(int a, int b);
  void draw();

};

#endif
