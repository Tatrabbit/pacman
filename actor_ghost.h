#ifndef _ACTOR_GHOST_H
#define _ACTOR_GHOST_H

/**
 * @file actor_ghost.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Pacman Ghost.
 */

#include "actor.h"
#include <SDL2/SDL.h>

/**
 * @memberof actor_s
 * @brief Initialize an actor_t as a ghost.
 * 
 * @param[in] kind Which ghost to initialize
 */
void pac_actor_ghost_reset(actor_t *, enum pac_actor_e kind);

#endif