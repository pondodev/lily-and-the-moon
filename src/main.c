#include "platform/app.h"
#include "game/game_manager.h"
#include "helpers.h"

// config
const size_t  WINDOW_WIDTH  = 400;
const size_t  WINDOW_HEIGHT = 240;
const char*   WINDOW_TITLE  = "lily and the moon (WIP)";
const uint8_t TARGET_FPS    = 60;

// contexts
extern AppContext app_context;
extern GameContext game_context;

void init(void) { init_platform(); init_game(); }
void cleanup(void) { cleanup_platform(); cleanup_game(); }

int main(void) {
    defer(init(), cleanup()) run_app();
    return 0;
}

