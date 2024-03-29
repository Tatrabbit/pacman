#ifndef _ACTOR_PACMAN_H
#define _ACTOR_PACMAN_H

/**
 * @file actor_pacman.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Pacman actor.
 */

#include "actor.h"
#include <SDL2/SDL.h>


/**
 * @memberof actor_s
 * @brief Initialize an actor_t as a Pacman.
 */
void pac_actor_pacman_reset(actor_t *);

/**
 * @memberof actor_s
 * @brief Handle keyboard input.
 * 
 * @param[in] evt Event from SDL. _Must_ be either SDL_KEYDOWN or SDL_KEYUP.
 */
void pac_actor_pacman_handle_keyboard(actor_t *, const SDL_Event *evt);

#endif