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

#endif

