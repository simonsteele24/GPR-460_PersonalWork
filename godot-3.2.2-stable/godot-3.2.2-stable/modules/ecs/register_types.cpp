#include "register_types.h"
#include "core/class_db.h"
#include "entity.h"

void register_ecs_types(){
	ClassDB::register_class<Entity>();
}

void unregister_ecs_types() {
}
