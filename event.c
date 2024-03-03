#include "event.h"


//////////////
// Internal //
//////////////

#define FRAME_DELAY 10u

/**
 * @brief the maximum length of the error buffer
 * @todo don't use this.
*/
#define PAC_EVENT_ERROR_BUFSIZE 256u


static struct
{
    /**
     * @brief String buffer.
     * 
     * This is used to share error message to main thread.
     * When this string is empty, assume there is currently no error.
     */
    char error[PAC_EVENT_ERROR_BUFSIZE];

    /**
     * @brief ID of the draw timer
     * 
     */
    SDL_TimerID timer_id;
} thread_info;

static int firstIndex;
static unsigned int redraw_timer(unsigned int time, void *param);


/////////////
// Externs //
/////////////

int pac_event_init()
{
    firstIndex = SDL_RegisterEvents(PAC_EVENT_COUNT);
    if (firstIndex < 0)
        return 0;

    thread_info.error[0] = '\0';

    thread_info.timer_id = SDL_AddTimer(FRAME_DELAY, redraw_timer, NULL);
    if (!thread_info.timer_id)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        return 0;
    }

    return 1;
}

void pac_event_cleanup()
{
    SDL_RemoveTimer(thread_info.timer_id);
}

int pac_event_poll_errors()
{
    if(!thread_info.error[0])
        return 0;

    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", thread_info.error);
    thread_info.error[0] = '\0';
    return 1;
}

void pac_event_adjust(SDL_Event *evt)
{
    evt->type -= firstIndex;
}

static unsigned int redraw_timer(unsigned int time, void *param)
{
    SDL_Event evt;

    memset(&evt, 0, sizeof(SDL_Event));
    evt.user.type = PAC_EVENT_DRAW + firstIndex;

    int error = SDL_PushEvent(&evt);
    if (error < 0)
    {
        const char *message = SDL_GetError();
        snprintf(thread_info.error, PAC_EVENT_ERROR_BUFSIZE, "%s", message);
    }
    return FRAME_DELAY;
}