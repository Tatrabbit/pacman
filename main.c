#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "event.h"

#define INIT_FLAGS (SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO)

enum _result
{
	_NOTHING = 0x0,
	_QUIT = 0x1,
	_DRAW = 0x2,
};

static enum _result handle_pac_event(SDL_Event *evt)
{
	switch(evt->type)
	{
		case PAC_EVENT_DRAW:
			printf("Timer\n");
			return _DRAW;
	}
	return _NOTHING;
}

static enum _result handle_sdl_event(SDL_Event *evt)
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

static int main_loop()
{
	thread_info info;
	SDL_Event evt;
	enum _result result;

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
	}

	end:
	pac_event_cleanup(&info);
	return (result & _QUIT) != 0;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(INIT_FLAGS) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("GAME",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    500, 500, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);

	int success = main_loop();

	SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

	return success;
}