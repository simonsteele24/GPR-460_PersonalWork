#include "register_types.h"
#include "core/class_db.h"
#include "entity.h"
#include "entityManager.h"
#include "component.h"

void register_ecs_types(){
	ClassDB::register_class<Entity>();
	ClassDB::register_class<EntityManager>();
	ClassDB::register_class<Component>();
}

void unregister_ecs_types() {
}
