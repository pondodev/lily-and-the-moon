#include "app.h"

#include "../game/game_manager.h"

AppContext app_context;

Texture2D tex;

void init_platform(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);
    init_keymap();

    app_context = (AppContext) {
        .delta_time = 0.f,
        .keymap = get_default_keymap(),
    };

    tex = LoadTexture("res/test.png");
}

void run_app(void) {
    while (poll_events()) {
        app_context.delta_time = GetFrameTime();

        update_game();
        render();
    }
}

int poll_events(void) {
    if (WindowShouldClose()) return 0;

    process_keymap(&app_context.keymap);

    return 1;
}

void render(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(10, 10, 30, 30, BLACK);
    DrawTexture(tex, 10, 50, WHITE);

    EndDrawing();
}

void cleanup(void) {
    UnloadTexture(tex);

    CloseWindow();
}

