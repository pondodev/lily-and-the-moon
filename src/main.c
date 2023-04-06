#include "platform/app.h"
#include "game/game_manager.h"

// config
const size_t  WINDOW_WIDTH  = 400;
const size_t  WINDOW_HEIGHT = 240;
const char*   WINDOW_TITLE  = "lily and the moon (WIP)";
const uint8_t TARGET_FPS    = 60;

// contexts
extern AppContext app_context;
extern GameContext game_context;

int main(void) {
    init_platform();
    init_game();

    run_app();
    cleanup();

    return 0;
}

