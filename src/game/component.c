#include "component.h"

#include <stdlib.h>
#include <string.h>

void* create_component(ComponentType type) {
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
            memset(c->path, 0, TEXTURE_PATH_MAX_LENGTH);
            c->id = 0;

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

void destroy_component(Component* component) {
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


