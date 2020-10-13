#include "catmullclarkRef.h"

CatmullClarkRef::CatmullClarkRef(){}

//Bind all your methods used in this class
void CatmullClarkRef::_bind_methods(){
  ClassDB::bind_method(D_METHOD("add", "a", "b"), &CatmullClarkRef::add);
  ClassDB::bind_method(D_METHOD("sub", "a", "b"), &CatmullClarkRef::sub);
  ClassDB::bind_method(D_METHOD("mul", "a", "b"), &CatmullClarkRef::mul);
  ClassDB::bind_method(D_METHOD("div", "a", "b"), &CatmullClarkRef::div);
}


//Custom Functions
int CatmullClarkRef::add(int a, int b) {
  return a+b;
}

int CatmullClarkRef::sub(int a, int b) {
  return a-b;
}

int CatmullClarkRef::mul(int a, int b) {
  return a*b;
}

int CatmullClarkRef::div(int a, int b) {
  return a/b;
}

