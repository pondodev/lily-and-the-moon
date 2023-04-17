#ifndef GAME_TYPES_H
#define GAME_TYPES_H

// game_types.h
// this is the public facing interface for types used in the game which the platform will
// use to display game state

#include <stdlib.h>

#include "../component_types.h"
#include "../entity_types.h"

typedef struct GameState {
    // TODO: what do we need?
    Entity* entities;
    size_t entity_count;
} GameState;

typedef struct GameAPI {
    GameState (*get_game_state)(void);
    void      (*set_game_state)(GameState state);
    void      (*init_game)(void);
    void      (*cleanup_game)(void);
    void      (*update_game)(void);
    // TODO: what other functions are needed?
} GameAPI;

#endif

