#ifndef _EVENT_H
#define _EVENT_H

#include <SDL2/SDL.h>

enum PacEvent
{
	PAC_EVENT_DRAW = 0,
	PAC_EVENT_COUNT
};

int pac_init_events();
void pac_adjust_event(SDL_Event *evt);

#endif