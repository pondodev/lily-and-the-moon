#include "entity_manager.h"

#include <stdio.h>
#include <string.h>

static Entity _entities[MAX_ENTITIES];
static size_t _entity_count = 0;

static void clear_entry(size_t index) {
    Entity* e = &_entities[index];

    e->id = -1;
    memset(e->name, '\0', ENTITY_NAME_CHARS_MAX);
    for (size_t i = 0; i < ENTITY_COMPONENT_COUNT_MAX; ++i) {
        if (e->components[i] != NULL)
            destroy_component(e->components[i]);

        e->components[i] = NULL;
    }
}

void init_entity_manager(void) {
    for (size_t i = 0; i < MAX_ENTITIES; ++i)
    {
        for (size_t j = 0; j < ENTITY_COMPONENT_COUNT_MAX; ++j)
            _entities[i].components[j] = NULL;

        clear_entry(i);
    }
}

Entity* create_entity(const char* name) {
    static size_t _current_id = 0;

    const size_t index = _entity_count;
    Entity* entity = &_entities[index];

    strncpy(entity->name, name, ENTITY_NAME_CHARS_MAX);
    entity->id = _current_id;

    ++_current_id;
    ++_entity_count;

    return entity;
}

void destroy_entity(int id) {
    int index = -1;

    for (size_t i = 0; i < MAX_ENTITIES; ++i) {
        if (_entities[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) return;
    clear_entry(index);
    // shuffle entities down the list
    for (size_t i = index; i < _entity_count; ++i) {
        memcpy(&_entities[i], &_entities[i + 1], sizeof(Entity));
        clear_entry(i + 1);
    }
}

void destroy_all_entities(void) {
    for (size_t i = 0; i < _entity_count; ++i) {
        if (_entities[i].id == -1) continue;
        clear_entry(i);
    }
}

Entity* get_entity_array(size_t* count) {
    *count = _entity_count;
    return _entities;
}

Entity* get_entity(size_t index) {
    return &_entities[index];
}

void set_entity_array(Entity* entities, size_t count) {
    memcpy(_entities, entities, MAX_ENTITIES);
    _entity_count = count;
}

void add_component_to_entity(Entity* const entity, Component* const component) {
    for (size_t i = 0; i < ENTITY_COMPONENT_COUNT_MAX; ++i) {
        if (entity->components[i] == NULL) {
            entity->components[i] = component;
            return;
        }
    }

    printf("unable to add component (id: %d) to entity \"%s\"\n", (int)component->type, entity->name);
}

