#include "app.h"
#include "board.h"
#include "event.h"
#include "texture.h"
#include "actor_pacman.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>

typedef enum
{
	_NOTHING = 0x0,
	_QUIT = 0x1,
	_FRAME = 0x2,
} result_t;


#define ACTOR_FIRST 0u

#define ACTOR_PACMAN 0u

// #define ACTOR_GHOST_FIRST 1u
// #define ACTOR_GHOST_LAST 4u

#define ACTOR_COUNT 1u

static actor_t actors[ACTOR_COUNT];

static int main_loop(const char *argv0);
static result_t handle_pac_event(SDL_Event *evt);
static result_t handle_sdl_event(SDL_Event *evt);

static void draw()
{
	// Clear to black
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

	// Draw
	pac_board_draw();

	for (int i = ACTOR_FIRST; i < ACTOR_COUNT; ++i)
		pac_actor_draw(&actors[i]);

	// Flip
    SDL_RenderPresent(app.renderer);
}

static int load_atlas(atlas_t *atlas, const char *argv0)
{
	char filename[PAC_STR_BUF_SIZE];
    if (!replace_basename(filename, argv0, "atlas.png"))
        return 0;

	return pac_atlas_init_image(atlas, filename);
}

static int initialize_atlases(atlas_t *tile_atlas, atlas_t *sprite_atlas, const char *argv0)
{
	// Tile Atlas
	tile_atlas->sheet_width = 200;
    tile_atlas->sheet_height = 186;
	tile_atlas->tile_size = PAC_TILE_SIZE;

    tile_atlas->margin_x = 1;
	tile_atlas->margin_y = 1;

	tile_atlas->sheet_padding_x = 1;
	tile_atlas->sheet_padding_y = 1;

	tile_atlas->n_sheets_w = 5;
    tile_atlas->n_sheets_h = 4;;

    tile_atlas->tile_padding_x = 1;
	tile_atlas->tile_padding_y = 1;
	
	tile_atlas->n_tiles_w = 22;

	// Texture
	if (!load_atlas(tile_atlas, argv0))
		return 0;

	// Sprite Atlas
	pac_atlas_init_atlas(sprite_atlas, tile_atlas);

	sprite_atlas->margin_y += 82;

	sprite_atlas->tile_size *= 2;
	sprite_atlas->n_tiles_w /= 2;
}

int main(int argc, const char *argv[])
{
	int error;
	if ((error = pac_app_init()))
		return error;

	int success = main_loop(argv[0]);

	pac_app_cleanup();
	return success;
}

// TODO create "main loop" modules for different scenes...
static int main_loop(const char *argv0)
{
	thread_info_t info;
	SDL_Event evt;
	result_t result = _NOTHING;

	if (!pac_event_init(&info))
		return -1;

	atlas_t tile_atlas, sprite_atlas;
	initialize_atlases(&tile_atlas, &sprite_atlas, argv0);

	pac_board_initialize(&tile_atlas);
	pac_actor_pacman_initialize(&actors[ACTOR_PACMAN], &sprite_atlas);

	// TODO ghosts

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

		if (result & _FRAME)
		{
			for (int i = 0; i < ACTOR_COUNT; ++i)
				(*actors[i].update)(&actors[i]);

			draw();
		}
	}

end:
	pac_atlas_destroy(&tile_atlas);
	pac_atlas_destroy(&sprite_atlas);

	pac_event_cleanup(&info);
	return (result & _QUIT) != 0;
}

static result_t handle_pac_event(SDL_Event *evt)
{
	switch(evt->type)
	{
		case PAC_EVENT_DRAW:
			return _FRAME;
	}
	return _NOTHING;
}

static result_t handle_sdl_event(SDL_Event *evt)
{
	switch (evt->type)
	{
		case SDL_QUIT:
			return _QUIT;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pac_actor_pacman_handle_keyboard(&actors[ACTOR_PACMAN], evt);
			return _NOTHING;
	}

	if (evt->type >= SDL_USEREVENT)
	{
		pac_event_adjust(evt);
		return handle_pac_event(evt);
	}
	return _NOTHING;
}