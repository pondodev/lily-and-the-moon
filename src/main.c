#include "app.h"

// config
const size_t WINDOW_WIDTH  = 400;
const size_t WINDOW_HEIGHT = 240;
const char*  WINDOW_TITLE  = "lily and the moon (WIP)";

int main(void) {
    init_platform();
    run();
    cleanup();

    return 0;
}

