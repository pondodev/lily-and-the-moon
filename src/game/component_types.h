#ifndef COMPONENT_TYPES
#define COMPONENT_TYPES

#include <stdint.h>

#include "types.h"

#define INHERIT_COMPONENT ComponentType type;

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
#define TEXTURE_PATH_MAX_LENGTH 100
typedef struct SpriteComponent {
    INHERIT_COMPONENT

    Vec2     offset;
    char     path[TEXTURE_PATH_MAX_LENGTH];
    uint32_t id;
} SpriteComponent;

typedef void (*TriggerCallback)(void);

// add collision detection to entity
// requires: PositionComponent
typedef struct CollisionComponent {
    INHERIT_COMPONENT

    int             trigger;
    TriggerCallback callback;
} CollisionComponent;

#endif

