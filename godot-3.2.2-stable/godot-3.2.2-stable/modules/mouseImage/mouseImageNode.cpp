#include "mouseImageNode.h"
#include "scene/resources/texture.h"
#include "core/bind/core_bind.h"
#include "scene/main/viewport.h"

MouseImageNode::MouseImageNode()
{
	canvas = VisualServer::get_singleton()->canvas_item_create();
}

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
	img.instance();
	img->load("icon.png");
	RID newTex = VisualServer::get_singleton()->texture_create_from_image(img);
	VisualServer::get_singleton()->canvas_item_set_visible(canvas, true);
	//VisualServer::get_singleton()->canvas_item_set_parent(canvas, get_viewport()->get_world_2d()->get_canvas());
	VisualServer::get_singleton()->canvas_item_add_circle(canvas,Point2(100,100),100.0f,Color(1,0,0));
	//VisualServer::get_singleton()->canvas_item_add_texture_rect(canvas, Rect2(Point2(200,200), Size2(Vector2(1000,1000))), newTex, false, Color(1,1,1), false, RID());
}

