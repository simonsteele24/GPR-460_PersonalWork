#include "mouseImageNode.h"

MouseImageNode::MouseImageNode() {}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("path", "a"), &MouseImageNode::path);
	ClassDB::bind_method(D_METHOD("location", "a", "b"), &MouseImageNode::location);
	ClassDB::bind_method(D_METHOD("draw"), &MouseImageNode::draw);
}


//Custom Functions
void MouseImageNode::path(String a) {
	imagePath = a;
}

void MouseImageNode::location(int a, int b) {
	iconLocationX = a;
	iconLocationY = b;
}

void MouseImageNode::draw() {
  return;
}

