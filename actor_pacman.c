#include "actor_pacman.h"
#include "board.h"
#include "globals.h"
#include <assert.h>

static const unsigned char pacman_anim[] = {39, 50};

static void update(actor_t *self);
static direction_t get_direction_from_keysym(SDL_Keycode sym);

#define MOVE_SPEED 60
#define ANIM_SPEED 80


/////////////
// Externs //
/////////////

void pac_actor_pacman_initialize(actor_t *pacman, const atlas_t *atlas)
{
    pacman->flags = 0;
    pacman->update = &update;

    pacman->move_distance = 0;
    pacman->current_tile[0] = 14;
    pacman->current_tile[1] = 20;

    pacman->_atlas = atlas;
	pacman->_tile = 61;
	pacman->_palette = 7;

    pacman->anim_frame = 0;
    pacman->_flip_state = SDL_FLIP_NONE;
}

void pac_actor_pacman_handle_keyboard(actor_t *pacman, const SDL_Event *evt)
{    
    int direction = get_direction_from_keysym(evt->key.keysym.sym) << 4;
    pacman->flags = (evt->type == SDL_KEYDOWN) ?
        (pacman->flags | direction) :
        (pacman->flags ^ direction);
}


////////////
// Static //
////////////

static void eat_pellet(actor_t *self)
{
    unit_t position[2];
    pac_actor_get_position(self, position);
    pac_board_eat(position);
}


static int try_start_direction(actor_t *self)
{
    direction_t direction = pac_purify_direction(self->flags >> 4);
    if (!direction)
        return 0;

    unit_t position[2];
    pac_actor_get_position(self, position);
    pac_add_direction_to_unit(position, PAC_UNITS_PER_TILE, direction);

    if (pac_board_kind(position) & PAC_TILE_WALL)
        return 0;

    self->flags = self->flags | direction;
    return 1;
}

static int try_reverse_direction(actor_t *self)
{
    direction_t current_direction, choice_direction;

    choice_direction = pac_purify_direction(self->flags >> 4);
    if (!choice_direction)
        return 0;

    current_direction = pac_purify_direction(self->flags & 0xf);
    if ( current_direction == choice_direction)
        return 0;

    if (!pac_same_axis(current_direction, choice_direction))
        return 0;

    // Reverse the location storage
    pac_add_direction_to_tile(self->current_tile, -1, choice_direction);
    self->move_distance = PAC_UNITS_PER_TILE - self->move_distance;

    return (self->flags = (self->flags & 0xf0) | choice_direction);
}

static int try_turn(actor_t *self)
{
    direction_t current_direction, choice_direction;

    choice_direction = pac_purify_direction(self->flags >> 4);
    if (!choice_direction)
        return 0;
    
    current_direction = pac_purify_direction(self->flags & 0xf);
    if ( current_direction == choice_direction)
        return 0;

    if (pac_same_axis(choice_direction, current_direction))
        return 0;

    unit_t position[2];
    pac_actor_get_position(self, position);
    pac_add_direction_to_unit(position, PAC_UNITS_PER_TILE, choice_direction);

    if (pac_board_kind(position) & PAC_TILE_WALL)
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
        self->move_distance %= PAC_UNITS_PER_TILE;
        pac_add_direction_to_tile(self->current_tile, 1, current_direction);

        unit_t position[2];
        pac_actor_get_position(self, position);
        pac_add_direction_to_unit(position, PAC_UNITS_PER_TILE, current_direction);
        if (pac_board_kind(position) & PAC_TILE_WALL)
        {
            self->move_distance = 0;
            self->flags = (self->flags & 0xf0);
        }
    }

    return overflow;
}

static int update_movement(actor_t *self)
{
    direction_t current_direction = pac_purify_direction(self->flags & 0xf);
    if ((!current_direction) && (!try_start_direction(self)) )
        return 0;

    try_reverse_direction(self);

    if (advance_movement(self))
    {
        try_turn(self);
        return 1;
    }

    return 0;
}

static void update_animation(actor_t *self)
{
    const size_t animation_length = 2;

    unsigned char flags = self->flags & 0xf;

    if (!flags) // Is moving?
        return;

    self->anim_frame += ANIM_SPEED;
    self->anim_frame %= PAC_UNITS_PER_TILE * animation_length;

    size_t frame = self->anim_frame / PAC_UNITS_PER_TILE;
    self->_tile = pacman_anim[frame];

    if (flags & PAC_DIRECTION_VERTICAL)
        self->_tile += 1;
  
    if (flags & PAC_DIRECTION_LEFT)
        self->_flip_state = SDL_FLIP_HORIZONTAL;
    else if (flags & PAC_DIRECTION_UP)
        self->_flip_state = SDL_FLIP_VERTICAL;
    else
        self->_flip_state = 0;
}

static void update(actor_t *self)
{
    if (update_movement(self))
        eat_pellet(self);

    update_animation(self);
}

static direction_t get_direction_from_keysym(SDL_Keycode sym)
{
    switch (sym)
    {
        case SDLK_LEFT:
            return PAC_DIRECTION_LEFT;
        case SDLK_RIGHT:
            return PAC_DIRECTION_RIGHT;
        case SDLK_DOWN:
            return PAC_DIRECTION_DOWN;
        case SDLK_UP:
            return PAC_DIRECTION_UP;
        default:
            return 0;
    }
}