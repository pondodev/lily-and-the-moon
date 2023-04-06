#ifndef COMPONENT_H
#define COMPONENT_H

#define INHERIT_COMPONENT ComponentType type;

#include <stdlib.h>
#include <stdint.h>

#include "types.h"
#include "../platform/texture_manager.h"

typedef enum ComponentType {
    COMPONENT_position  = 0,
    COMPONENT_render    = 1,
    COMPONENT_rect      = 2,
    COMPONENT_sprite    = 3,
    COMPONENT_collision = 4,
} ComponentType;

// base component, cast to this for storage and check `type` field to know
// what the component is
typedef struct Component {
    INHERIT_COMPONENT
} Component;

// give entity a position on the map
// requires: none
typedef struct PositionComponent {
    INHERIT_COMPONENT

    Vec2 position;
} PositionComponent;

typedef enum RenderLayer {
    RENDERLAYER_ground  = 0,
    RENDERLAYER_props   = 1,
} RenderLayer;

// define how an entity should be rendered
// requires: none
typedef struct RenderComponent {
    INHERIT_COMPONENT

    RenderLayer layer;
} RenderComponent;

// render entity as rect
// requires: PositionComponent, RenderComponent
typedef struct RectComponent {
    INHERIT_COMPONENT

    Vec2 offset;
    Vec2 dimensions;
} RectComponent;

// render entity as sprite
// requires: PositionComponent, RenderComponent
typedef struct SpriteComponent {
    INHERIT_COMPONENT

    Vec2             offset;
    AbstractTexture* sprite;
} SpriteComponent;

typedef void (*TriggerCallback)(void);

// add collision detection to entity
// requires: PositionComponent
typedef struct CollisionComponent {
    INHERIT_COMPONENT

    int             trigger;
    TriggerCallback callback;
} CollisionComponent;

static inline Component* create_component(ComponentType type) {
    Component* to_return = NULL;

    switch (type) {
        case COMPONENT_position:
        {
            PositionComponent* c = malloc(sizeof(PositionComponent));
            c->position = (Vec2) { .x = 0, .y = 0 };

            to_return = (Component*)c;
            break;
        }

        case COMPONENT_render:
        {
            RenderComponent* c = malloc(sizeof(RenderComponent));
            c->layer = RENDERLAYER_props;

            to_return = (Component*)c;
            break;
        }

        case COMPONENT_rect:
        {
            RectComponent* c = malloc(sizeof(RectComponent));
            c->offset = (Vec2) { .x = 0, .y = 0 };
            c->dimensions = (Vec2) { .x = 0, .y = 0 };

            to_return = (Component*)c;
            break;
        }

        case COMPONENT_sprite:
        {
            SpriteComponent* c = malloc(sizeof(SpriteComponent));
            c->sprite = NULL;

            to_return = (Component*)c;
            break;
        }

        case COMPONENT_collision:
        {
            CollisionComponent* c = malloc(sizeof(CollisionComponent));
            c->trigger = 0;
            c->callback = NULL;

            to_return = (Component*)c;
            break;
        }

        // NOTE: don't use default case to ensure compiler error catches missing case
    }

    to_return->type = type;
    return to_return;
}

static inline void destroy_component(Component* component) {
    switch (component->type) {
        case COMPONENT_position:
        case COMPONENT_render:
        case COMPONENT_rect:
        case COMPONENT_sprite: // you need to tell the platform when you wish to free a texture
        case COMPONENT_collision:
            break;

        // NOTE: don't use default case to ensure compiler error catches missing case
    }

    free(component);
}

#endif

