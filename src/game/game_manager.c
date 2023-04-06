#include "game_manager.h"

#include "entity_manager.h"

GameContext game_context;

void init_game(void) {
    game_context = (GameContext) {
        .camera_position = (Vec2) { .x = 0, .y = 0 },
    };

    init_entity_manager();
}

void update_game(void) {
    // TODO
}

