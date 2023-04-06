#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "raylib.h"

#define MAX_TEXTURES 10
#define TEXTURE_ALIAS_MAX_LENGTH 16
#define TEXTURE_PATH_MAX_LENGTH 128

// abstract reference to a platform's texture for the game to use
typedef struct AbstractTexture {
    char alias[TEXTURE_ALIAS_MAX_LENGTH];
    char path[TEXTURE_PATH_MAX_LENGTH];
    int active;
    Texture2D texture;
} AbstractTexture;

void init_texture_manager(void);
AbstractTexture* create_texture(const char* alias, const char* path);
AbstractTexture* get_texture(const char* alias);
void free_texture(const char* alias);
void free_all_textures(void);

#endif

