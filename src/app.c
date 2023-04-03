#include "app.h"

void init_platform(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: failed to init SDL\n");
        print_error();
        exit(1);
    }

    const uint32_t window_flags = 0;
    context.window = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            window_flags);

    if (! context.window) {
        printf("ERROR: failed to create window\n");
        print_error();
        exit(1);
    }

    const uint32_t renderer_flags = SDL_RENDERER_ACCELERATED;
    context.renderer = SDL_CreateRenderer(context.window, -1, renderer_flags);
    if (! context.renderer) {
        printf("ERROR: failed to create renderer\n");
        print_error();
        exit(1);
    }
}

void print_error(void) {
#ifdef SDL_h_
    const char* errMsg = SDL_GetError();
    printf("SDL_GetError: %s\n", errMsg);
    SDL_ClearError();
#endif
}

void run(void) {
    while (poll_events()) {
        render();
    }
}

int poll_events(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;

            // TODO

            default:
                break;
        }
    }

    return 1;
}

void render(void) {
    SDL_SetRenderDrawColor(context.renderer, 50, 50, 50, 255);
    SDL_RenderClear(context.renderer);

    const SDL_Rect rect = { 10, 10, 20, 20 };
    SDL_SetRenderDrawColor(context.renderer, 200, 200, 210, 255);
    SDL_RenderFillRect(context.renderer, &rect);

    SDL_RenderPresent(context.renderer);
}

void cleanup(void) {
    SDL_DestroyRenderer( context.renderer );
    SDL_DestroyWindow( context.window );
    SDL_Quit();
}

