#include "actor_pacman.h"
#include "actor.h"
#include "board.h"
#include "globals.h"
#include <assert.h>

// static const unsigned char pacman_anim_h[] = {39, 50};

static void update(actor_t *self);
static direction_t get_direction_from_keysym(SDL_Keycode sym);

const int speed = 60;

void pac_actor_pacman_initialize(actor_t *pacman)
{
    pacman->flags = 0;
    pacman->update = &update;

    pacman->move_distance = 0;
    pacman->current_tile[0] = 14;
    pacman->current_tile[1] = 20;

	pacman->tile_idx = 61;
	pacman->palette_idx = 7;
}

void pac_actor_pacman_handle_keyboard(actor_t *pacman, SDL_Event *evt)
{    
    int direction = get_direction_from_keysym(evt->key.keysym.sym) << 4;
    pacman->flags = (evt->type == SDL_KEYDOWN) ?
        (pacman->flags | direction) :
        (pacman->flags ^ direction);
}

// static int check_tile_free(const unit_t tile[2])
// {
//     // unit_t snapped_pos[2];
//     // snapped_pos[0] = pac_tiles2units(tile[0]);
//     // snapped_pos[1] = pac_tiles2units(tile[1]);

//     return !(pac_board_kind(tile) & PAC_TILE_WALL);
// }

static int try_start_moving(actor_t *self)
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

// static void try_turn(actor_t *self)
// {
// }

// static void try_change_direction(actor_t *self)
// {
//     direction_t choice_direction = pac_purify_direction((self->flags & 0xf0) >> 4);
//     if (!choice_direction)
//         return;

//     tile_t choice_tile[2];
//     memcpy(choice_tile, self->current_tile, sizeof(tile_t) * 2);

//     pac_add_direction_to_tile(choice_tile, 1, choice_direction);
//     if (!check_tile_free(choice_tile) )
//         return;

//     self->flags = (self->flags & 0xf0) | choice_direction;
// }

static int advance_movement(actor_t *self, direction_t current_direction)
{
    // Advance pixels
    self->move_distance += speed;
    int overflow = self->move_distance >= PAC_UNITS_PER_TILE;

    // Advance tiles, re-advance pixels
    if (overflow)
    {
        self->move_distance %= PAC_UNITS_PER_TILE;
        pac_add_direction_to_tile(self->current_tile, 1, current_direction);
    }

    return overflow;
}

static void update(actor_t *self)
{
    direction_t current_direction = pac_purify_direction(self->flags & 0xf);
    if (!current_direction && !try_start_moving(self) )
        return;

    // try_reverse(self);

    int overflow;
    overflow = advance_movement(self, current_direction);

    // if (overflow)
    // {
    //     try_turn(self);

    //     overflow = advance_movement(self);
    //     assert(!overflow);
    // }

    // Assign to draw position
    // pac_actor_actual_position(self, self->pos);
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