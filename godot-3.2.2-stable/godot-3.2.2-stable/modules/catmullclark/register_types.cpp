#include "register_types.h"
#include "core/class_db.h"
#include "subdivisionNode.h"

void register_catmullclark_types(){
	ClassDB::register_class<SubdivisionNode>();
	
}

void unregister_catmullclark_types() {
}
