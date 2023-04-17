#include "texture_manager.h"

#include <stdlib.h>
#include <string.h>

static AbstractTexture _textures[MAX_TEXTURES];
static size_t          _texture_count = 0;

static void clear_info(size_t index) {
    AbstractTexture* texture = &_textures[index];

    texture->generation = 0;
    texture->active = 0;
}

void init_texture_manager(void) {
    for (size_t i = 0; i < MAX_TEXTURES; ++i) {
        clear_info(i);
    }
}

uint32_t create_texture(const char* path) {
    const uint16_t index = _texture_count;
    AbstractTexture* texture = &_textures[index];

    ++texture->generation;
    texture->active = 1;
    texture->texture = LoadTexture(path);

    ++_texture_count;
    return ((uint32_t)(texture->generation) << 8) | index;
}

AbstractTexture* get_texture(const uint32_t id) {
    const uint16_t index = id & 0x00FF;
    const uint16_t gen = (id & 0xFF00) >> 8;

    if (index >= _texture_count) return NULL;

    AbstractTexture* texture = &_textures[index];
    return texture->generation == gen && texture->active ? texture : NULL;
}

void free_texture(const uint32_t id) {
    AbstractTexture* texture = get_texture(id);
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

