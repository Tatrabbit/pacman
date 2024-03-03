#include "game.h"
#include "texture.h"
#include "event.h"
#include "globals.h"

static result_t handle_pac_event(SDL_Event *evt)
{
	switch(evt->type)
	{
		case PAC_EVENT_DRAW:
			return _FRAME;
	}

	// TODO

	return _NOTHING;
}

static result_t handle_sdl_event(SDL_Event *evt, scene_t *scene)
{
	result_t result = (*scene->handle_sdl_event)(evt);

	switch (evt->type)
	{
		case SDL_QUIT:
			return result | _QUIT;
	}

	if (evt->type >= SDL_USEREVENT)
	{
		pac_event_adjust(evt);
		return handle_pac_event(evt);
	}

	return result;
}

static int load_atlas(atlas_t *atlas, const char *argv0)
{
	char filename[PAC_STR_BUF_SIZE];
    if (!replace_basename(filename, argv0, "atlas.png"))
        return 0;

	return pac_atlas_init_image(atlas, filename);
}

static int initialize_atlases(const char *argv0)
{
	atlas_t *tile_atlas = app.tile_atlas;
	atlas_t *sprite_atlas = app.sprite_atlas;

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

	return 1;
}

static void draw(scene_t *scene)
{
	// Clear to black
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);

	scene->draw(scene);

	// Flip
    SDL_RenderPresent(app.renderer);
}

result_t scene_loop_inner(scene_t *scene)
{
	for ( ;; )
	{
		SDL_Event evt;

		if (!SDL_WaitEvent(&evt))
		{
			printf("Error: %s\n", SDL_GetError());
			return _ERROR;
		}

		pac_event_poll_errors();

		result_t result = _NOTHING;
		do
		{
			result |= handle_sdl_event(&evt, scene);
			if(result & _QUIT)
				return _QUIT;
		}
		while (SDL_PollEvent(&evt));

		if (result & _FRAME)
		{
			scene->update(scene);
			draw(scene);
		}
	}

	return _NOTHING;
}

static result_t scene_loop_outer(scene_t *scene)
{
	if (scene->initialize)
		scene->initialize(scene);

	result_t result = scene_loop_inner(scene);

	if (scene->free)
		scene->free(scene);

	return result;
}

static int outer_loop_all(const char *argv0)
{
	SDL_Event evt;

	// Systems
	if (!pac_event_init())
		return _ERROR;

	// Media
	atlas_t tile_atlas, sprite_atlas;
	app.tile_atlas = &tile_atlas;
	app.sprite_atlas = &sprite_atlas;

	initialize_atlases(argv0);

	scene_t scene;

	// Game:
	pac_game_get_scene(&scene);
	result_t result = scene_loop_outer(&scene);

	pac_atlas_destroy(&tile_atlas);
	pac_atlas_destroy(&sprite_atlas);

	pac_event_cleanup();
	return (result & _QUIT) != 0;
}

int main(int argc, const char *argv[])
{
	app.argc = argc;
	app.argv = argv;

	int error;
	if ((error = pac_app_init()))
		return error;

	int success = outer_loop_all(argv[0]);

	pac_app_cleanup();
	return success;
}