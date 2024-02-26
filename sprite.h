#ifndef _SPRITE_H
#define _SPRITE_H

#include "texture.h"
#include "globals.h"
#include <SDL2/SDL.h>

typedef struct
{
    tex_idx_t tex_idx;
    unit_t pos[2];
    unsigned char flags;
} sprite_t;


/**
 * @brief Draw a sprite.
 * 
 * This is preferable to using pac_tex_draw_sprite, because it takes into account
 * tile/pixel space conversion.
 * 
 * @param sprite Sprite to draw.
 */
void pac_sprite_draw(const sprite_t *sprite);


#endif