#ifndef _EVENT_H
#define _EVENT_H

#include <SDL2/SDL.h>

typedef struct
{
    char error[256];
    SDL_TimerID timer_id;
} thread_info;

enum pac_event
{
	PAC_EVENT_DRAW = 0,
	PAC_EVENT_COUNT
};

int pac_event_init(thread_info *info);
void pac_event_cleanup(thread_info *info);
void pac_event_adjust(SDL_Event *evt);
int pac_event_poll_errors(thread_info *info);

#endif