#ifndef ENTITY_TYPES_H
#define ENTITY_TYPES_H

#include "component_types.h"

#define MAX_ENTITIES 100 // TODO: tweak to true min value
#define ENTITY_NAME_CHARS_MAX 16
#define ENTITY_COMPONENT_COUNT_MAX 50 // TODO: tweak to true min value

typedef struct Entity {
    int        id;
    char       name[ENTITY_NAME_CHARS_MAX];
    Component* components[ENTITY_COMPONENT_COUNT_MAX];
} Entity;

#endif

