#ifndef COMPONENT_H
#define COMPONENT_H

#include "component_types.h"

void* create_component(ComponentType type);
void destroy_component(Component* component);

#endif

