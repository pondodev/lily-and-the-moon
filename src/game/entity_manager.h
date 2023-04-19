#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdint.h>
#include <stdlib.h>

#include "entity_types.h"
#include "component.h"

void init_entity_manager(int first_load);
void restore_entity_manager(Entity* entities, size_t entity_count);
void cleanup_entity_manager(void);
Entity* create_entity(const char* name);
void destroy_entity(int id);
void destroy_all_entities(void);
Entity* get_entity_array(size_t* count);
Entity* get_entity(size_t index);
void add_component_to_entity(Entity* const entity, Component* const component);

#endif

