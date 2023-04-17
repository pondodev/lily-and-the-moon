#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "raylib.h"

#include <stdint.h>

#define MAX_TEXTURES 10
#define TEXTURE_ALIAS_MAX_LENGTH 16
#define TEXTURE_PATH_MAX_LENGTH 256

// abstract reference to a platform's texture for the game to use
typedef struct AbstractTexture {
    uint16_t generation;
    int active;
    Texture2D texture;
} AbstractTexture;

void init_texture_manager(void);
uint32_t create_texture(const char* path);
AbstractTexture* get_texture(const uint32_t id);
void free_texture(const uint32_t id);
void free_all_textures(void);

#endif

