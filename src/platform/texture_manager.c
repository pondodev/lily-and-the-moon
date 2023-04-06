#include "texture_manager.h"

#include <stdlib.h>
#include <string.h>

static AbstractTexture _textures[MAX_TEXTURES];
static size_t          _texture_count = 0;

static void clear_info(size_t index) {
    AbstractTexture* texture = &_textures[index];
    memset(texture->alias, '\0', TEXTURE_ALIAS_MAX_LENGTH);
    memset(texture->path, '\0', TEXTURE_PATH_MAX_LENGTH);
    texture->active = 0;
}

void init_texture_manager(void) {
    for (size_t i = 0; i < MAX_TEXTURES; ++i) {
        clear_info(i);
    }
}

AbstractTexture* create_texture(const char* alias, const char* path) {
    size_t index = _texture_count;
    AbstractTexture* texture = &_textures[index];

    strncpy(texture->alias, alias, TEXTURE_ALIAS_MAX_LENGTH);
    strncpy(texture->path, path, TEXTURE_PATH_MAX_LENGTH);

    ++_texture_count;
    return texture;
}

AbstractTexture* get_texture(const char* alias) {
    for (size_t i = 0; i < MAX_TEXTURES; ++i) {
        if (strncmp(alias, _textures[i].alias, TEXTURE_ALIAS_MAX_LENGTH))
            return &_textures[i];
    }

    return NULL;
}

void free_texture(const char* alias) {
    AbstractTexture* texture = get_texture(alias);
    if (texture == NULL) return;

    size_t index = texture - _textures;
    clear_info(index);
    UnloadTexture(texture->texture);
    --_texture_count;

    // shuffle textures down the list
    for (size_t i = index; i < _texture_count; ++i) {
        memcpy(&_textures[i], &_textures[i + 1], sizeof(AbstractTexture));
        clear_info(i + 1);
    }
}

void free_all_textures(void) {
    for (size_t i = 0; i < _texture_count; ++i) {
        UnloadTexture(_textures[i].texture);
        clear_info(i);
    }

    _texture_count = 0;
}

