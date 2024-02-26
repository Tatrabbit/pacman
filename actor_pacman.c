#include "actor_pacman.h"
#include "sprite.h"
#include "globals.h"

// static const unsigned char pacman_anim_h[] = {39, 50};

static void update(actor_t *self);
static direction_t get_direction_from_keysym(SDL_Keycode sym);

const int speed = 60;

void pac_actor_pacman_initialize(actor_t *pacman)
{
    pacman->flags = 0;
    pacman->update = &update;

    pacman->sprite.pos[0] = pac_tiles2units(13);
    pacman->sprite.pos[1] = pac_tiles2units(16);

	pacman->sprite.tex_idx.tile_idx = 61;
	pacman->sprite.tex_idx.palette_idx = 7;
}

void pac_actor_pacman_handle_keyboard(actor_t *pacman, SDL_Event *evt)
{    
    int direction = get_direction_from_keysym(evt->key.keysym.sym) << 4;
    pacman->flags = (evt->type == SDL_KEYDOWN) ?
        (pacman->flags | direction) :
        (pacman->flags ^ direction);
}

static void apply_direction(const unit_t current_pos[2], unit_t pos[2], direction_t flags)
{
    memcpy(pos, current_pos, sizeof(unit_t) * 2);

    // Horizontal movement takes precedence
    if (flags & PAC_DIRECTION_LEFT)
        pos[0] = current_pos[0] - speed;
    else if ( flags & PAC_DIRECTION_RIGHT )
        pos[0] = current_pos[0] + speed;
    else if ( flags & PAC_DIRECTION_UP )
        pos[1] = current_pos[1] - speed;
    else if ( flags & PAC_DIRECTION_DOWN )
        pos[1] = current_pos[1] + speed;
}

static void update(actor_t *self)
{
    direction_t current_direction, next_direction;
    current_direction = self->flags & 0x0f;
    next_direction = (self->flags & 0xf0) >> 4;

    unit_t next_pos[2];
    apply_direction(self->sprite.pos, next_pos, current_direction);

    // No direction is pressed:
    if (!next_direction)
        goto move;

    // Same direction is pressed:
    if (current_direction & next_direction)
        goto move;

change_direction:
    self->flags = (self->flags & 0xf0) | next_direction;
    apply_direction(self->sprite.pos, next_pos, next_direction);

move:
    memcpy(self->sprite.pos, next_pos, sizeof(unit_t) * 2);
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