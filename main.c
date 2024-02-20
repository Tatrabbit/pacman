#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "app.h"
#include "event.h"
#include "pacman.h"

typedef enum
{
	_NOTHING = 0x0,
	_QUIT = 0x1,
	_DRAW = 0x2,
} result_t;

static result_t handle_pac_event(SDL_Event *evt)
{
	switch(evt->type)
	{
		case PAC_EVENT_DRAW:
			return _DRAW;
	}
	return _NOTHING;
}

static result_t handle_sdl_event(SDL_Event *evt)
{
	switch (evt->type)
	{
		case SDL_QUIT:
			return _QUIT;
	}

	if (evt->type >= SDL_USEREVENT)
	{
		pac_event_adjust(evt);
		return handle_pac_event(evt);
	}
	return _NOTHING;
}

static void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

static void draw(pacman_t *pacman)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

	blit(pacman->texture, pacman->x, pacman->y);

    SDL_RenderPresent(app.renderer);
}

static int main_loop()
{
	thread_info info;
	SDL_Event evt;
	result_t result = _NOTHING;

	pacman_t pacman;
	pac_pac_create(&pacman);

	if (!pac_event_init(&info))
		return -1;

	while (1)
	{
		if (!SDL_WaitEvent(&evt))
		{
			printf("Error: %s\n", SDL_GetError());
			return -1;
		}

		pac_event_poll_errors(&info);

		result = _NOTHING;
		do
		{
			result |= handle_sdl_event(&evt);
			if(result & _QUIT)
				goto end;
		}
		while (SDL_PollEvent(&evt));

		if (result & _DRAW)
			draw(&pacman);
	}

	end:
	pac_event_cleanup(&info);
	return (result & _QUIT) != 0;
}

int main(int argc, char *argv[])
{
	int error;
	if ((error = pac_app_init()))
		return error;

	int success = main_loop();

	pac_app_cleanup();
	return success;
}