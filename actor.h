#ifndef _ACTOR_H
#define _ACTOR_H

#include "globals.h"

enum
{
    PAC_DIRECTION_NONE = 0b0000,

    PAC_DIRECTION_LEFT  = 0b0001,
    PAC_DIRECTION_RIGHT = 0b0010,
    PAC_DIRECTION_UP    = 0b0100,
    PAC_DIRECTION_DOWN  = 0b1000,

    PAC_DIRECTION_HORIZONTAL = (PAC_DIRECTION_LEFT | PAC_DIRECTION_RIGHT),
    PAC_DIRECTION_VERTICAL   = (PAC_DIRECTION_UP | PAC_DIRECTION_DOWN),

    PAC_DIRECTION_NEGATIVE = (PAC_DIRECTION_LEFT | PAC_DIRECTION_UP),
    PAC_DIRECTION_POSITIVE = (PAC_DIRECTION_RIGHT | PAC_DIRECTION_DOWN),
};

typedef unsigned char direction_t;

typedef struct actor_s
{
    // tex_idx_t:
    unsigned char tile_idx;
    unsigned char palette_idx;
    //

    /**
     * @brief Update this actor, called once before each draw()
     */
    void (*update)(struct actor_s *self);

    tile_t current_tile[2];
    unit_t move_distance;

    direction_t flags;
} actor_t;

direction_t pac_purify_direction(direction_t flags);
int pac_same_axis(direction_t a, direction_t b);

void pac_add_direction_to_tile(tile_t tile[2], tile_t amount, direction_t flags);
void pac_add_direction_to_unit(unit_t tile[2], unit_t amount, direction_t flags);

void pac_actor_get_position(const actor_t *self, unit_t position[2]);

/**
 * @brief Draw a sprite.
 * 
 * This is preferable to using pac_tex_draw_sprite, because it takes into account
 * tile/pixel space conversion.
 * 
 * @param sprite Sprite to draw.
 */
void pac_actor_draw(const actor_t *actor);

#endif