#include "entity_manager.h"

#include <string.h>

static Entity _entities[MAX_ENTITIES];
static size_t _entity_count = 0;

static void clear_entry(size_t index);

void init_entity_manager(void) {
    for (size_t i = 0; i < MAX_ENTITIES; ++i)
        clear_entry(i);
}

Entity* create_entity(const char* name) {
    static size_t _current_id = 0;

    const size_t index = _entity_count;
    Entity* entity = &_entities[index];

    strncpy(entity->name, name, ENTITY_NAME_CHARS_MAX);
    entity->id = _current_id;

    // this shouldn't be needed, but i'm dumb so...
    for (size_t i = 0; i < ENTITY_COMPONENT_COUNT_MAX; ++i) {
        if (entity->components[i] != NULL)
            destroy_component(entity->components[i]);
    }

    ++_current_id;
    ++_entity_count;

    return entity;
}

static void clear_entry(size_t index) {
    Entity* e = &_entities[index];

    e->id = -1;
    memset(e->name, '\0', ENTITY_NAME_CHARS_MAX);
    for (size_t i = 0; i < ENTITY_COMPONENT_COUNT_MAX; ++i) {
        if (e->components[i] != NULL)
            destroy_component(e->components[i]);
    }
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
    for (size_t i = index + 1; i < MAX_ENTITIES; ++i) {
        // end of the collection of entities, delete trailing entry
        if (_entities[i].id == -1) {
            clear_entry(i - 1);
            return;
        }

        memcpy(&_entities[i - 1], &_entities[i], sizeof(Entity));
    }
}

Entity* get_entity_array(size_t* count) {
    *count = _entity_count;
    return _entities;
}

Entity* get_entity(size_t index) {
    return &_entities[index];
}
