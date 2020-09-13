#include "mouseImageRef.h"

MouseImageRef::MouseImageRef() {}

//Bind all your methods used in this class
void MouseImageRef::_bind_methods(){
	ClassDB::bind_method(D_METHOD("add", "a"), &MouseImageRef::add);
	ClassDB::bind_method(D_METHOD("sub", "a", "b"), &MouseImageRef::sub);
	ClassDB::bind_method(D_METHOD("mul", "a", "b"), &MouseImageRef::mul);
	ClassDB::bind_method(D_METHOD("div", "a", "b"), &MouseImageRef::div);
}


//Custom Functions
String MouseImageRef::add(String a) {
  return a;
}

int MouseImageRef::sub(int a, int b) {
  return a-b;
}

int MouseImageRef::mul(int a, int b) {
  return a*b;
}

int MouseImageRef::div(int a, int b) {
  return a/b;
}

