#ifndef _SPRITE_H
#define _SPRITE_H

#include "texture.h"
#include <SDL2/SDL.h>

typedef struct
{
    int x;
    int y;
    tex_idx_t tex_idx;
} sprite_t;

#endif