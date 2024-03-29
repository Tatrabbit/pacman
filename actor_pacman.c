#include "actor_pacman.h"
#include "board.h"
#include "globals.h"
#include <assert.h>

static const unsigned char pacman_anim[] = {39, 50};

static void update(actor_t *self);
static direction_t get_direction_from_keysym(SDL_Keycode sym);

#define MOVE_SPEED 60


/////////////
// Externs //
/////////////

void pac_actor_pacman_reset(actor_t *pacman)
{
    memset(pacman, 0, sizeof(actor_t));

    pacman->update = &update;
    pacman->draw = &pac_actor_draw;

    pacman->current_tile[0] = 13;
    pacman->current_tile[1] = 26;

	pacman->_tile = 61;
	pacman->_palette = 7;

    pacman->_actor_flags = PAC_ACTOR_PLAYER;
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

    if (pac_board_kind_unit(position) & PAC_TILE_WALL)
        return 0;

    self->flags = self->flags | direction;
    return 1;
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

    if (pac_board_kind_unit(position) & PAC_TILE_WALL)
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
    direction_t current_direction = pac_purify_direction(self->flags & 0xf);
    if ((!current_direction) && (!try_start_direction(self)) )
        return 0;

    pac_actor_try_reverse_direction_(self);

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

    unit_t anim_frame = pac_actor_anim_frame % (PAC_UNITS_PER_TILE * 2);
    anim_frame %= PAC_UNITS_PER_TILE * animation_length;

    size_t frame = anim_frame / PAC_UNITS_PER_TILE;
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