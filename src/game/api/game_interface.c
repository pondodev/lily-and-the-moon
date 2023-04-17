#include "game_interface.h"

#include "game_manager.h"

static const GameAPI api = {
    .get_game_state = get_game_state,
    .set_game_state = set_game_state,
    .init_game = init_game,
    .cleanup_game = cleanup_game,
    .update_game = update_game,
};

const GameAPI* get_game_api(void) {
    return &api;
}

