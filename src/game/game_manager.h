#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "types.h"

typedef struct GameContext {
    Vec2 camera_position;
} GameContext;

void init_game(void);
void update_game(void);

#endif

