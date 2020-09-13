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

  String add(String a);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);

};

#endif
