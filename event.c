#include "event.h"

#define FRAME_DELAY 10

static int firstIndex;

static unsigned int redraw_timer(unsigned int time, void *_)
{
    SDL_Event evt;
    memset(&evt, 0, sizeof(SDL_Event));
    evt.user.type = PAC_EVENT_DRAW + firstIndex;

    SDL_PushEvent(&evt);
    return FRAME_DELAY;
}

int pac_init_events()
{
    firstIndex = SDL_RegisterEvents(PAC_EVENT_COUNT);
    if (firstIndex < 0)
        return 0;

    SDL_AddTimer(FRAME_DELAY, redraw_timer, 0);
    return 1;
}

void pac_adjust_event(SDL_Event *evt)
{
    evt->type -= firstIndex;
}