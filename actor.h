#ifndef _ACTOR_H
#define _ACTOR_H

#include "sprite.h"

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

typedef unsigned char direction_t;

typedef struct actor_s
{
    sprite_t sprite;

    /**
     * @brief Update this actor, called once before each draw()
     */
    void (*update)(struct actor_s *self);

    unsigned char flags;
} actor_t;

#endif