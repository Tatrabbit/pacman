#ifndef _EVENT_H
#define _EVENT_H
/**
 * @file event.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Handles App-specific events.
 */

#include <SDL2/SDL.h>


/**
 * @brief SDL User events
 */
enum pac_event_e
{
	PAC_EVENT_DRAW = 0,
	PAC_EVENT_COUNT
};

/**
 * @brief Initializer.
 * @return int non-zero on success
 */
int pac_event_init();

/**
 * @brief Destructor.
 */
void pac_event_cleanup();

/**
 * @brief Convert from SDL event space to user event space.
 * 
 * If an event type >= `SDL_USEREVENT`, call this function.
 * Then, the event type will correspond directly with pac_event enum.
 * 
 * @param[in,out] evt The event to modify.
 */
void pac_event_adjust(SDL_Event *evt);

/**
 * @brief Check for errors handling events, and logs them.
 * @return non-zero if an error was reported.
 * 
 * This should be called repeatedly every frame, until it returns 0.
 */
int pac_event_poll_errors();

#endif