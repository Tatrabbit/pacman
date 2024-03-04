#include "actor_ghost.h"
#include "board.h"

#define MOVE_SPEED 60

static void update(actor_t *self);
static void draw(const actor_t *self);
static void pick_scatter_target(actor_t *self);

void pac_actor_ghost_reset(actor_t *self, enum pac_actor_e kind)
{
    memset(self, 0, sizeof(actor_t));

    self->update = &update;
    self->draw = &draw;

    self->current_tile[0] = 13;
    self->current_tile[1] = 14;

	self->_tile = 0;
	self->_palette = 0;

    unsigned int next_direction = PAC_DIRECTION_LEFT << 4;
    self->_actor_flags = kind | next_direction;
    self->flags = next_direction;

    pick_scatter_target(self);
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

static unsigned int find_target_distance(const actor_t *self, tile_t choice[2])
{
    unsigned int x, y;
    x = choice[0] - self->_target_tile[0];
    y = choice[1] - self->_target_tile[1];

    return x*x + y*y;
}

static unsigned int pick_direction(actor_t *self)
{
    unsigned int shortest_distance = -1, best_direction;
    unsigned int from_direction = self->_actor_flags >> 4;

    // foreach direction
    for (unsigned int i = 4; i--; )
    {
        // Don't reverse!
        unsigned int direction = 0x1 << i;
        if (direction & from_direction)
            continue;

        // Calculate adjacent tile
        tile_t choice[2];
        memcpy(choice, self->current_tile, sizeof(tile_t) * 2u);
        pac_add_direction_to_tile(choice, 1, direction);

        // Can't go into walls
        if (pac_board_kind_tile(choice) & PAC_TILE_WALL)
            continue;

        // Find shortest
        float distance = find_target_distance(self, choice);
        if ( distance < shortest_distance )
        {
            shortest_distance = distance;
            best_direction = direction;
        }
    }

    return best_direction;
}

static void update_target_direction(actor_t *self)
{
    unsigned int new_flags = pick_direction(self);

    self->_actor_flags &= 0x0f;
    self->_actor_flags |= pac_get_opposite_direction(new_flags) << 4u;

    self->flags &= 0x0f;
    self->flags |= new_flags << 4u;
}

static void pick_target_blinky(actor_t *self)
{
    tile_t *target = pac_actors[PAC_ACTOR_PLAYER].current_tile;
    memcpy(self->_target_tile, target, sizeof(tile_t) * 2);
}

static void pick_scatter_target(actor_t *self)
{
    switch ( self->_actor_flags & 0xf)
    {
    case PAC_ACTOR_BLINKY:
        self->_target_tile[0] = PAC_SCREEN_TILES_W - 4;
        self->_target_tile[1] = 0;
        break;
    }
}

static void pick_chase_target(actor_t *self)
{
    switch ( self->_actor_flags & 0xf)
    {
    case PAC_ACTOR_BLINKY:
        return pick_target_blinky(self);
    }
}

static void pick_target(actor_t *self)
{
    pick_chase_target(self);
    update_target_direction(self);
}

static void update_animation(actor_t *self)
{
    const int animation_length = 2;

    int direction = self->flags & 0xf;
    int frame = get_anim_index(direction);

    unit_t current_frame = pac_actor_anim_frame % (PAC_UNITS_PER_TILE * animation_length);
    frame += current_frame / PAC_UNITS_PER_TILE;

    self->_tile = frame;
}


static int try_start_direction(actor_t *self)
{
    direction_t direction = self->flags >> 4;
    if (!direction)
        return 0;

    self->flags = self->flags | direction;
    return 1;
}

static int try_turn(actor_t *self)
{
    direction_t current_direction, choice_direction;

    choice_direction = self->flags >> 4;
    if (!choice_direction)
        return 0;
    
    current_direction = self->flags & 0xf;
    if (current_direction == choice_direction)
        return 0;

    if (pac_same_axis(choice_direction, current_direction))
        return 0;
    
    return self->flags = (self->flags & 0xf0) | choice_direction;
}

static int advance_movement(actor_t *self)
{
    direction_t current_direction;
    current_direction = self->flags & 0xf;

    // Advance pixels
    self->move_distance += MOVE_SPEED;
    int overflow = self->move_distance >= PAC_UNITS_PER_TILE;

    // Advance tiles, re-advance pixels
    if (overflow)
    {
        self->move_distance -= PAC_UNITS_PER_TILE;
        pac_add_direction_to_tile(self->current_tile, 1, current_direction);

        unit_t position[2];
        pac_actor_get_position(self, position);
        pac_add_direction_to_unit(position, PAC_UNITS_PER_TILE, current_direction);
        if (pac_board_kind_unit(position) & PAC_TILE_WALL)
        {
            self->move_distance = 0;
            self->flags = (self->flags & 0xf0);
        }
    }

    return overflow;
}

static int update_movement(actor_t *self)
{
    const unsigned int speed = 60;

    direction_t current_direction = self->flags & 0xf;
    if ((!current_direction) && (!try_start_direction(self)))
        return 0;

    // try_reverse_direction(self);

    if (advance_movement(self))
    {
        pick_target(self);
        try_turn(self);
        return 1;
    }

    return 0;
}

static void update(actor_t *self)
{
    update_movement(self);
    update_animation(self);
}

static void draw(const actor_t *self)
{
    // Draw target
    const int target_index = 49;

    pixel_t x, y;
    x = pac_tiles2pixels(self->_target_tile[0]);
    y = pac_tiles2pixels(self->_target_tile[1]);

    pac_atlas_draw_tile(app.sprite_atlas, target_index, self->_palette, (int)x, (int)y, 0);

    // Base
    pac_actor_draw(self);
}