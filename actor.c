#include "actor.h"
#include <assert.h>

void pac_actor_get_position(const actor_t *self, unit_t position[2])
{
    position[0] = pac_tiles2units(self->current_tile[0]);
    position[1] = pac_tiles2units(self->current_tile[1]);
}

void pac_actor_draw(const actor_t *self)
{
    unit_t position[2];
    pixel_t x, y;

    assert(self->move_distance < PAC_UNITS_PER_TILE);
    pac_actor_get_position(self, position);
    pac_add_direction_to_unit(position, self->move_distance, self->flags);

    assert(sizeof(pixel_t) >= sizeof(int));
    x = pac_units2pixels(position[0]);
    y = pac_units2pixels(position[1]);

    x += -3;
    y += -3;

    pac_tile_draw(&self->tile, (int)x, (int)y);
}

direction_t pac_purify_direction(direction_t flags)
{
    // Horizontal movement takes precedence
    if (flags & PAC_DIRECTION_LEFT)
        return PAC_DIRECTION_LEFT;

    else if ( flags & PAC_DIRECTION_RIGHT )
        return PAC_DIRECTION_RIGHT;

    else if ( flags & PAC_DIRECTION_UP )
        return PAC_DIRECTION_UP;

    else if ( flags & PAC_DIRECTION_DOWN )
        return PAC_DIRECTION_DOWN;

    else
        return 0;
}

int pac_same_axis(direction_t a, direction_t b)
{
    direction_t overlap = a | b;

    direction_t h = (overlap & PAC_DIRECTION_HORIZONTAL) != 0;
    direction_t v = (overlap & PAC_DIRECTION_VERTICAL) != 0;

    return h != v;
}

// Horizontal movement takes precedence
#define ADD_DEFINE(t) void pac_add_direction_to_##t ( t##_t t[2], t ## _t amount, direction_t flags) { \
    if (flags & PAC_DIRECTION_LEFT) \
        t[0] -= amount; \
    else if ( flags & PAC_DIRECTION_RIGHT ) \
        t[0] += amount; \
    else if ( flags & PAC_DIRECTION_UP ) \
        t[1] -= amount; \
    else if ( flags & PAC_DIRECTION_DOWN ) \
        t[1] += amount; }

ADD_DEFINE(tile)
ADD_DEFINE(unit)
#undef ADD_DEFINE