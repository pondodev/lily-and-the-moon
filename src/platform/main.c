#include "app.h"
#include "../helpers.h"
#include "../game/api/game_types.h"

#include <dlfcn.h>

// config
const size_t  WINDOW_WIDTH  = 400;
const size_t  WINDOW_HEIGHT = 240;
const char*   WINDOW_TITLE  = "lily and the moon (WIP)";
const uint8_t TARGET_FPS    = 60;
#if defined(__APPLE__)
    const char* GAME_LIB_PATH = "libgame.dylib";
#elif defined(__linux__)
    #error linux support todo
#elif defined(__MINGW32__ || __WIN32__)
    #error windows support todo
#else
    #error unsupported platform!
#endif

typedef GameAPI* (*get_game_api_t)(void);
const GameAPI* api = NULL;

void init(void) { init_platform(); api->init_game(); }
void cleanup(void) { cleanup_platform(); api->cleanup_game(); }

int main(void) {
    void* game_lib = dlopen(GAME_LIB_PATH, RTLD_NOW); // TODO: make this cross platform
    get_game_api_t get_game_api = (get_game_api_t)dlsym(game_lib, "get_game_api");
    api = get_game_api();

    defer(init(), cleanup()) run_app();
    return 0;
}

