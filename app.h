#ifndef _APP_H
#define _APP_H

#include <SDL2/SDL.h>

typedef struct
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} app_t;

#ifndef _APP_C
extern
#endif
app_t app;

int pac_app_init();
void pac_app_cleanup();

#endif