#include "app.h"

#include "../helpers.h"
#include "../game/api/game_types.h"

AppContext app_context;
extern const GameAPI* api;

Texture2D tex;

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
        ClearBackground(RAYWHITE);
        DrawRectangle(10, 10, 30, 30, BLACK);
        DrawTexture(tex, 10, 50, WHITE);
    }
}

void cleanup_platform(void) {
    UnloadTexture(tex);
}

