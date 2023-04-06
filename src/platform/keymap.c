#include "keymap.h"

static void process_keymap_entry(KeymapEntry* entry) {
    entry->state = IsKeyUp(entry->keycode) ? KEYSTATE_Up : KEYSTATE_Down;
    entry->pressed = IsKeyPressed(entry->keycode);
}

const Keymap kDefaultKeymap = {
    .menu   = (KeymapEntry) { .keycode = KEY_ESCAPE, .state = KEYSTATE_Up, .pressed = 0 },

    .left   = (KeymapEntry) { .keycode = KEY_A, .state = KEYSTATE_Up, .pressed = 0 },
    .right  = (KeymapEntry) { .keycode = KEY_D, .state = KEYSTATE_Up, .pressed = 0 },
    .up     = (KeymapEntry) { .keycode = KEY_W, .state = KEYSTATE_Up, .pressed = 0 },
    .down   = (KeymapEntry) { .keycode = KEY_S, .state = KEYSTATE_Up, .pressed = 0 },

    .select = (KeymapEntry) { .keycode = KEY_ESCAPE, .state = KEYSTATE_Up, .pressed = 0 },
    .back   = (KeymapEntry) { .keycode = KEY_ESCAPE, .state = KEYSTATE_Up, .pressed = 0 },
};

void init_keymap(void) {
    SetExitKey(-1); // HACK: we don't want an exit key, set it to an invalid keycode
}

Keymap get_default_keymap(void) {
    return kDefaultKeymap;
}

void process_keymap(Keymap* keymap) {
    process_keymap_entry(&keymap->menu);
    process_keymap_entry(&keymap->left);
    process_keymap_entry(&keymap->right);
    process_keymap_entry(&keymap->up);
    process_keymap_entry(&keymap->down);
    process_keymap_entry(&keymap->select);
    process_keymap_entry(&keymap->back);
}

