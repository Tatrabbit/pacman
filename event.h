#ifndef _EVENT_H
#define _EVENT_H
/**
 * @file event.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Handles App-specific events.
 * @todo Refactor into singleton.
 */

#include <SDL2/SDL.h>

/**
 * @brief the maximum length of the error buffer
 * @todo don't use this.
*/
#define PAC_EVENT_ERROR_BUFSIZE 256u

/**
 * @brief Class representing an instance of this file.
 */
typedef struct thread_info_s
{
    char error[PAC_EVENT_ERROR_BUFSIZE];
    SDL_TimerID timer_id;
} thread_info_t;

/**
 * @brief SDL User events
 */
enum pac_event
{
	PAC_EVENT_DRAW = 0,
	PAC_EVENT_COUNT
};

/**
 * @brief Constructor.
 * @memberof thread_info_s
 * @return int non-zero on success
 */
int pac_event_init(thread_info_t *);

/**
 * @memberof thread_info_s
 * @brief Destructor.
 */
void pac_event_cleanup(thread_info_t *);

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
int pac_event_poll_errors(thread_info_t *info);

#endif