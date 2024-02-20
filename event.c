#include "event.h"

#define FRAME_DELAY 10u

static int firstIndex;
static unsigned int redraw_timer(unsigned int time, void *param);

int pac_event_init(thread_info_t *info)
{
    firstIndex = SDL_RegisterEvents(PAC_EVENT_COUNT);
    if (firstIndex < 0)
        return 0;

    info->error[0] = '\0';

    info->timer_id = SDL_AddTimer(FRAME_DELAY, redraw_timer, info);
    if (!info->timer_id)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        return 0;
    }

    return 1;
}

void pac_event_cleanup(thread_info_t *info)
{
    SDL_RemoveTimer(info->timer_id);
}

int pac_event_poll_errors(thread_info_t *info)
{
    if(!info->error[0])
        return 0;

    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", info->error);
    info->error[0] = '\0';
    return 1;
}

void pac_event_adjust(SDL_Event *evt)
{
    evt->type -= firstIndex;
}

static unsigned int redraw_timer(unsigned int time, void *param)
{
    thread_info_t *info = (thread_info_t *)param;
    SDL_Event evt;

    memset(&evt, 0, sizeof(SDL_Event));
    evt.user.type = PAC_EVENT_DRAW + firstIndex;

    int error = SDL_PushEvent(&evt);
    if (error < 0)
    {
        const char *message = SDL_GetError();
        snprintf(info->error, PAC_EVENT_ERROR_BUFSIZE, "%s", message);
    }
    return FRAME_DELAY;
}