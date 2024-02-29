#include "actor_ghost.h"

static void update(actor_t *self);
static void draw(const actor_t *self);

void pac_actor_ghost_initialize(actor_t *self, const atlas_t *atlas, enum pac_actor_e kind)
{
    memset(self, 0, sizeof(actor_t));

    self->update = &update;
    self->draw = &draw;

    self->current_tile[0] = 13;
    self->current_tile[1] = 14;

    self->_atlas = atlas;

	self->_tile = 0;
	self->_palette = 0;

    self->_actor_kind = kind;
}

static int get_anim_index(int direction)
{
    switch (direction)
    {
    case PAC_DIRECTION_RIGHT:
        return 0;
    case PAC_DIRECTION_DOWN:
        return 2;
    case PAC_DIRECTION_LEFT:
        return 4;
    case PAC_DIRECTION_UP:
    default:
        return 6;
    }
}

static void update(actor_t *self)
{
    const int animation_length = 2;

    int direction = self->flags & 0xf;
    int frame = get_anim_index(direction);

    unit_t current_frame = pac_actor_anim_frame % (PAC_UNITS_PER_TILE * animation_length);
    frame += current_frame / PAC_UNITS_PER_TILE;

    self->_tile = frame;
}

static void draw(const actor_t *self)
{
    pac_actor_draw(self);
}