#ifndef _ACTOR_PACMAN_H
#define _ACTOR_PACMAN_H

#include "actor.h"
#include <SDL2/SDL.h>

/**
 * @brief Initialize an actor_t as a Pacman.
 * 
 * @param pacman Pointer to data to initialize.
 */
void pac_actor_pacman_initialize(actor_t *pacman);


/**
 * @brief Handle keyboard input.
 * 
 * @param pacman Existing actor.
 * @param evt Event from SDL. _Must_ be either SDL_KEYDOWN or SDL_KEYUP.
 */
void pac_actor_pacman_handle_keyboard(actor_t *pacman, SDL_Event *evt);

#endif