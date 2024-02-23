#ifndef _SPRITE_H
#define _SPRITE_H

#include "texture.h"
#include <SDL2/SDL.h>

enum
{
    PAC_DIRECTION_NONE = 0b0000,

    PAC_DIRECTION_LEFT  = 0b0001,
    PAC_DIRECTION_RIGHT = 0b0010,
    PAC_DIRECTION_UP    = 0b0100,
    PAC_DIRECTION_DOWN  = 0b1000,

    PAC_DIRECTION_HORIZONTAL = 0b0011,
    PAC_DIRECTION_VERTICAL   = 0b1100,
};

typedef struct
{
    tex_idx_t tex_idx;

    // Measured in PAC_UNITS_PER_PIXEL:
    unsigned short x;
    unsigned short y;

    unsigned char flags;
} sprite_t;

void pac_sprite_initialize();
void pac_sprite_draw_all();

#endif