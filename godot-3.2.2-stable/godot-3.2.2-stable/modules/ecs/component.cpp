#include "component.h"

Component::Component(){}

//Bind all your methods used in this class
void Component::_bind_methods(){
  ClassDB::bind_method(D_METHOD("add", "a", "b"), &Component::add);
  ClassDB::bind_method(D_METHOD("sub", "a", "b"), &Component::sub);
  ClassDB::bind_method(D_METHOD("mul", "a", "b"), &Component::mul);
  ClassDB::bind_method(D_METHOD("div", "a", "b"), &Component::div);
}


//Custom Functions
int Component::add(int a, int b) {
  return a+b;
}

int Component::sub(int a, int b) {
  return a-b;
}

int Component::mul(int a, int b) {
  return a*b;
}

int Component::div(int a, int b) {
  return a/b;
}

