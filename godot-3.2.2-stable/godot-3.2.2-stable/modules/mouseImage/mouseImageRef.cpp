#include "mouseImageRef.h"

MouseImageRef::MouseImageRef() {}

//Bind all your methods used in this class
void MouseImageRef::_bind_methods(){
	ClassDB::bind_method(D_METHOD("path", "a"), &MouseImageRef::path);
	ClassDB::bind_method(D_METHOD("location", "a", "b"), &MouseImageRef::location);
	ClassDB::bind_method(D_METHOD("draw"), &MouseImageRef::draw);
}


//Custom Functions
void MouseImageRef::path(String a) {
  return;
}

void MouseImageRef::location(int a, int b) {
  return;
}

void MouseImageRef::draw() {
  return;
}

