#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entity_manager.h"
#include "component.h"

typedef struct GameContext {
    Entity* player;
} GameContext;

void init_game(void);
void cleanup_game(void);
void update_game(void);

#endif

