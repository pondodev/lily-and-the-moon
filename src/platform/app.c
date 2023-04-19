#include "app.h"

#include "../helpers.h"
#include "../game/api/game_types.h"

#include <dlfcn.h>
#include <sys/stat.h>
#include <stdio.h>

// TODO
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
void* game_lib = NULL;
struct timespec game_lib_mod_time;

AppContext app_context;

Texture2D tex;

void reload_game_lib(void) {
    if (game_lib != NULL) {
        api = NULL;
        dlclose(game_lib);
    }

    game_lib = dlopen(GAME_LIB_PATH, RTLD_NOW);
    get_game_api_t get_game_api = (get_game_api_t)dlsym(game_lib, "get_game_api");
    api = get_game_api();

    struct stat lib_stat;
    stat(GAME_LIB_PATH, &lib_stat);
    game_lib_mod_time = lib_stat.st_mtimespec;
}

int is_game_lib_updated(void) {
    struct stat lib_stat;
    const int err = stat(GAME_LIB_PATH, &lib_stat);
    if (err != 0) return 0;

    return game_lib_mod_time.tv_sec != lib_stat.st_mtimespec.tv_sec;
}

void init_platform(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(TARGET_FPS);
    init_keymap();

    app_context = (AppContext) {
        .delta_time = 0.f,
        .keymap = get_default_keymap(),
        .exiting = 0,
    };

    tex = LoadTexture("res/test.png");
}

void run_app(void) {
    while (poll_events()) {
        if (is_game_lib_updated()) {
            printf("detected change in game library! reloading...\n");
            const GameState state = api->get_game_state();
            reload_game_lib();
            api->init_game(0);
            api->set_game_state(state);
        }

        app_context.delta_time = GetFrameTime();

        api->update_game();
        render();
    }
}

int poll_events(void) {
    if (app_context.keymap.menu.pressed) { // TODO: temp
        CloseWindow();
        app_context.exiting = 1;
    }

    if (WindowShouldClose() || app_context.exiting) return 0;

    process_keymap(&app_context.keymap);

    return 1;
}

void render(void) {
    defer(BeginDrawing(), EndDrawing()) {
        ClearBackground(WHITE);
        DrawRectangle(10, 10, 30, 30, BLACK);
        DrawTexture(tex, 10, 50, WHITE);
    }
}

void cleanup_platform(void) {
    UnloadTexture(tex);
}

