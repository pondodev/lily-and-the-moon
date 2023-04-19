#include "game_manager.h"

GameContext game_context;

GameState get_game_state(void) {
    GameState state;

    state.entities = get_entity_array(&state.entity_count);

    return state;
}

void set_game_state(GameState state) {
    restore_entity_manager(state.entities, state.entity_count);
    // TODO: set game context
}

void init_game(int first_load) {
    init_entity_manager(first_load);

    if (! first_load) return;
    game_context = (GameContext) {
        .player = create_entity("player"),
    };

    // player component init
    {
        PositionComponent* pos = create_component(COMPONENT_position);
        *pos = (PositionComponent) {
            .type = pos->type,
            .position = (Vec2) { .x = 0, .y = 0 },
        };
        add_component_to_entity(game_context.player, (Component*)pos);

        RectComponent* rect = create_component(COMPONENT_rect);
        *rect = (RectComponent) {
            .type = rect->type,
            .dimensions = (Vec2) { .x = 16, .y = 16 },
            .offset = (Vec2) { .x = 0, .y = 0 },
        };
        add_component_to_entity(game_context.player, (Component*)rect);

        RenderComponent* render = create_component(COMPONENT_render);
        *render = (RenderComponent) {
            .type = render->type,
            .layer = RENDERLAYER_props
        };
        add_component_to_entity(game_context.player, (Component*)render);
    }
}

void update_game(void) {
    // TODO
}

void cleanup_game(void) {
    destroy_all_entities(); // TODO: we only need to call this to free components, handle this in component refactor
    cleanup_entity_manager();
}

