#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entity_manager.h"
#include "component.h"
#include "api/game_interface.h"

typedef struct GameContext {
    Entity* player;
} GameContext;

GameState get_game_state(void);
void set_game_state(GameState state);

void init_game(void);
void cleanup_game(void);
void update_game(void);

#endif

