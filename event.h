#ifndef _EVENT_H
#define _EVENT_H

#include <SDL2/SDL.h>

#define PAC_EVENT_ERROR_BUFSIZE 256u

typedef struct
{
    char error[PAC_EVENT_ERROR_BUFSIZE];
    SDL_TimerID timer_id;
} thread_info_t;

enum pac_event
{
	PAC_EVENT_DRAW = 0,
	PAC_EVENT_COUNT
};

int pac_event_init(thread_info_t *info);
void pac_event_cleanup(thread_info_t *info);

/**
 * @brief Convert from SDL event space to user event space.
 * 
 * If an event type >= SDL_USEREVENT, call this function.
 * Then, the event type will correspond directly with pac_event enum.
 * 
 * @param event to modify
 */
void pac_event_adjust(SDL_Event *evt);

/**
 * @brief Check for errors handling events, and logs them.
 * This should be called every frame.
 * @return non-zero if there was an error.
 */
int pac_event_poll_errors(thread_info_t *info);

#endif