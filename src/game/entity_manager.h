#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdint.h>

#include "component.h"

#define MAX_ENTITIES 100 // TODO: tweak to true min value
#define ENTITY_NAME_CHARS_MAX 16
#define ENTITY_COMPONENT_COUNT_MAX 50 // TODO: tweak to true min value

typedef struct Entity {
    int        id;
    char       name[ENTITY_NAME_CHARS_MAX];
    Component* components[ENTITY_COMPONENT_COUNT_MAX];
} Entity;

void init_entity_manager(void);
Entity* create_entity(const char* name);
void destroy_entity(int id);
Entity* get_entity_array(size_t* count);
Entity* get_entity(size_t index);

#endif

