#include "actor_pacman.h"
#include "sprite.h"

// static const unsigned char pacman_anim_h[] = {39, 50};

static void update(actor_t *self);
static int get_direction_from_keysym(SDL_Keycode sym);


void pac_actor_pacman_initialize(actor_t *pacman)
{
    pacman->flags = 0;
    pacman->update = &update;

    pac_sprite_set_pos((sprite_t *)pacman, 13u, 16u);

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

static void update(actor_t *self)
{
    const int speed = 100;
    
    int debug_direction = self->flags >> 4;

    // Horizontal movement takes precedence
    if (debug_direction & PAC_DIRECTION_HORIZONTAL)
    {
        if (debug_direction & PAC_DIRECTION_LEFT)
            self->sprite.x -= speed;
        else if (debug_direction & PAC_DIRECTION_RIGHT)
            self->sprite.x += speed;
    }
    else
    {
        if (debug_direction & PAC_DIRECTION_UP)
            self->sprite.y -= speed;
        else if (debug_direction & PAC_DIRECTION_DOWN)
            self->sprite.y += speed;
    }
}

static int get_direction_from_keysym(SDL_Keycode sym)
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