#include "app.h"
#include "board.h"
#include "event.h"
#include "sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>

typedef enum
{
	_NOTHING = 0x0,
	_QUIT = 0x1,
	_DRAW = 0x2,
} result_t;

static int main_loop();
static result_t handle_pac_event(SDL_Event *evt);
static result_t handle_sdl_event(SDL_Event *evt);


static void draw()
{
	// Clear to black
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

	// Draw
	pac_board_draw();
	pac_sprite_draw_all();

	// Flip
    SDL_RenderPresent(app.renderer);
}

int main(int argc, char *argv[])
{
	int error;
	if ((error = pac_app_init()))
		return error;

	pac_tex_init(argv[0]);

	int success = main_loop();

	pac_app_cleanup();
	return success;
}

// TODO create "main loop" modules for different scenes...
static int main_loop()
{
	thread_info_t info;
	SDL_Event evt;
	result_t result = _NOTHING;

	if (!pac_event_init(&info))
		return -1;

	pac_sprite_initialize();

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
			draw();
	}

	end:
	pac_event_cleanup(&info);
	return (result & _QUIT) != 0;
}

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