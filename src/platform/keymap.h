#ifndef KEYMAP_H
#define KEYMAP_H

#include "raylib.h"

typedef enum KeyState {
    KEYSTATE_Up,
    KEYSTATE_Down,
} KeyState;

typedef struct KeymapEntry {
    int      keycode;
    KeyState state;
    int pressed; // true when key was pressed this frame
} KeymapEntry;

typedef struct Keymap {
    KeymapEntry menu;

    KeymapEntry left;
    KeymapEntry right;
    KeymapEntry up;
    KeymapEntry down;

    KeymapEntry select;
    KeymapEntry back;
} Keymap;

void init_keymap(void);
Keymap get_default_keymap(void);
void process_keymap(Keymap* keymap);

// TODO: create way to modify keymap?

#endif

