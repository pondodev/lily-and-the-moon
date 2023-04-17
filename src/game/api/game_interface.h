#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

// game_interface.h
// this is the public facing interface for the game's api which the platform will use to get and
// set certain game states

#include "game_types.h"

const GameAPI* get_game_api(void);

#endif

