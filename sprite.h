#ifndef _SPRITE_H
#define _SPRITE_H

#include "texture.h"
#include <SDL2/SDL.h>

typedef struct
{
    tex_idx_t tex_idx;

    // Measured in PAC_UNITS_PER_PIXEL:
    unsigned short x;
    unsigned short y;

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

/**
 * @brief Set position.
 * 
 * @param sprite Sprite to act upon.
 * @param x x position, specified in tiles.
 * @param y y position, specified in tiles.
 */
void pac_sprite_set_pos(sprite_t *sprite, unsigned short x, unsigned short y);

#endif