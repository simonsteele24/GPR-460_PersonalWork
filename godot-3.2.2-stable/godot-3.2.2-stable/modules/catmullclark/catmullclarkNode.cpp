#include "catmullclarkNode.h"

CatmullClarkNode::CatmullClarkNode(){}

//Bind all your methods used in this class
void CatmullClarkNode::_bind_methods(){
  ClassDB::bind_method(D_METHOD("add", "a", "b"), &CatmullClarkNode::add);
  ClassDB::bind_method(D_METHOD("sub", "a", "b"), &CatmullClarkNode::sub);
  ClassDB::bind_method(D_METHOD("mul", "a", "b"), &CatmullClarkNode::mul);
  ClassDB::bind_method(D_METHOD("div", "a", "b"), &CatmullClarkNode::div);
}


//Custom Functions
int CatmullClarkNode::add(int a, int b) {
  return a+b;
}

int CatmullClarkNode::sub(int a, int b) {
  return a-b;
}

int CatmullClarkNode::mul(int a, int b) {
  return a*b;
}

int CatmullClarkNode::div(int a, int b) {
  return a/b;
}

