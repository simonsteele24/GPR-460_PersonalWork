#include "register_types.h"
#include "core/class_db.h"
#include "catmullclarkNode.h"
#include "catmullclarkRef.h"

void register_catmullclark_types(){
	ClassDB::register_class<CatmullClarkNode>();
	ClassDB::register_class<CatmullClarkRef>();
}

void unregister_catmullclark_types() {
}
