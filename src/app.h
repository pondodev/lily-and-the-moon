#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <SDL.h>

// platform specific details in here. this should be the main area to
// change when porting to a new platform

// config (set in main.c)
extern const size_t WINDOW_WIDTH;
extern const size_t WINDOW_HEIGHT;
extern const char*  WINDOW_TITLE;

// global state for the application
typedef struct AppContext
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
} AppContext;

AppContext context;

// initialise engine before gameplay starts
void init_platform(void);

// print out errors held by the framework/os based on last operation
void print_error(void);

// run the main game loop
void run(void);

// handle all events dependant on framework/platform here
int poll_events(void);

// draw the game state to screen
void render(void);

// called before application closes. cleanup resources, persist data
void cleanup(void);

#endif

