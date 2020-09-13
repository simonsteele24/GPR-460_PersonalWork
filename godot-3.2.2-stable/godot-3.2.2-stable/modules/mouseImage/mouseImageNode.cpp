#include "mouseImageNode.h"

MouseImageNode::MouseImageNode() {}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add", "a"), &MouseImageNode::add);
	ClassDB::bind_method(D_METHOD("sub", "a", "b"), &MouseImageNode::sub);
	ClassDB::bind_method(D_METHOD("mul", "a", "b"), &MouseImageNode::mul);
	ClassDB::bind_method(D_METHOD("div", "a", "b"), &MouseImageNode::div);
}


//Custom Functions
String MouseImageNode::add(String a) {
  return a;
}

int MouseImageNode::sub(int a, int b) {
  return a-b;
}

int MouseImageNode::mul(int a, int b) {
  return a*b;
}

int MouseImageNode::div(int a, int b) {
  return a/b;
}

