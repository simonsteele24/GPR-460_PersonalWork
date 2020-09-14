#include "mouseImageNode.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"

MouseImageNode::MouseImageNode() {}

//Bind all your methods used in this class
void MouseImageNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("path", "a"), &MouseImageNode::path);
	ClassDB::bind_method(D_METHOD("location", "a", "b"), &MouseImageNode::location);
	ClassDB::bind_method(D_METHOD("draw"), &MouseImageNode::draw);
	ClassDB::bind_method(D_METHOD("getmouselocation"), &MouseImageNode::getMouseLocation);
}


//Custom Functions
void MouseImageNode::path(String a) {
	imagePath = a;
}

void MouseImageNode::location(int a, int b) {
	iconLocationX = a;
	iconLocationY = b;
}

Point2 MouseImageNode::getMouseLocation()
{
	return OS::get_singleton()->get_mouse_position();
}

void MouseImageNode::draw()
{
	Ref<Image> img;
	Ref<ImageTexture> itex;
	img.instance();
	img->load("C:\\Users\\simon\\Desktop\\bestboi.jpg");
	//itex->create_from_image(*img);
	itex->draw(itex->get_rid(), Point2(iconLocationX, iconLocationY));
}

