#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

// game_interface.h
// this is the public facing interface for the game's api which the platform will use to get and
// set certain game states

#include "game_types.h"

#include <stdlib.h>

typedef struct GameAPI {
    GameState (*get_game_state)(void);
    void      (*set_game_state)(GameState state);
    void      (*init_game)(void);
    void      (*cleanup_game)(void);
    void      (*update_game)(void);
    // TODO: what other functions are needed?
} GameAPI;

const GameAPI* get_game_api(void);

#endif

