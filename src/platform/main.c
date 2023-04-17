#include "app.h"
#include "../helpers.h"
#include "../game/api/game_interface.h"

// config
const size_t  WINDOW_WIDTH  = 400;
const size_t  WINDOW_HEIGHT = 240;
const char*   WINDOW_TITLE  = "lily and the moon (WIP)";
const uint8_t TARGET_FPS    = 60;

extern GameAPI* api;

void init(void) { init_platform(); api->init_game(); }
void cleanup(void) { cleanup_platform(); api->cleanup_game(); }

int main(void) {
    defer(init(), cleanup()) run_app();
    return 0;
}

