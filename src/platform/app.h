#ifndef APP_H
#define APP_H

#include "raylib.h"

#include "keymap.h"

#include <stdlib.h>
#include <time.h>

// platform specific details in here. this should be the main area to
// change when porting to a new platform

// config (set in main.c)
extern const size_t  WINDOW_WIDTH;
extern const size_t  WINDOW_HEIGHT;
extern const char*   WINDOW_TITLE;
extern const uint8_t TARGET_FPS;

// global state for the application
typedef struct AppContext {
    float delta_time;
    Keymap keymap;
    int exiting;
} AppContext;

// important! call this before you try to interact with the game api at all!!
void reload_game_lib(void);

// check if the game library has been updated for hot reloading
int is_game_lib_updated(void);

// initialise engine before gameplay starts
void init_platform(void);

// run the main game loop
void run_app(void);

// handle all events dependant on framework/platform here
int poll_events(void);

// draw the game state to screen
void render(void);

// called before application closes. cleanup resources, persist data
void cleanup_platform(void);

#endif

