#include "register_types.h"
#include "core/class_db.h"
#include "mouseImageRef.h"
#include "mouseImageNode.h"

void register_mouseImage_types(){
	ClassDB::register_class<MouseImageNode>();
	ClassDB::register_class<MouseImageRef>();
}

void unregister_mouseImage_types() {
}
