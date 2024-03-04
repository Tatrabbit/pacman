#include "game.h"
#include "actor_pacman.h"
#include "actor_ghost.h"
#include "actor.h"
#include "board.h"
#include "texture.h"
#include "event.h"
#include <SDL2/SDL.h>


//////////////
// Internal //
//////////////
#define INTRO_TIME 3000

static unsigned char pac_lives;

static int scene_timer;


static unsigned int actor_overlap(const actor_t *a, const actor_t *b)
{
    unit_t pa[2], pb[2];

    pac_actor_get_position(a, pa);
    pac_actor_get_position(b, pb);

    unit_t size = PAC_UNITS_PER_TILE;

    if ((pa[0] + size) < pb[0])
        return 0;
    if (pa[0] > (pb[0] + size))
        return 0;

    if ((pa[1] + size) < pb[1])
        return 0;
    if (pa[1] > (pb[1] + size))
        return 0;

    return 1;
}

static result_t handle_sdl_event(SDL_Event *evt)
{
	switch (evt->type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pac_actor_pacman_handle_keyboard(&pac_actors[PAC_ACTOR_PLAYER], evt);
	}

    return PAC_RESULT_NOTHING;
}


//////////
// Draw //
//////////

static void draw_life(pixel_t x)
{
    pixel_t y = pac_tiles2pixels(PAC_SCREEN_TILES_H - 2);

    const unsigned int palette = 7;
    unsigned int tile = 154;

    // TODO make a draw 2x2
    pac_atlas_draw_tile(app.tile_atlas, tile, palette, x, y, 0);
    pac_atlas_draw_tile(app.tile_atlas, tile + 1, palette, x + PAC_TILE_SIZE, y, 0);

    tile += 22;
    y += PAC_TILE_SIZE;
    pac_atlas_draw_tile(app.tile_atlas, tile, palette, x, y, 0);
    pac_atlas_draw_tile(app.tile_atlas, tile + 1, palette, x + PAC_TILE_SIZE, y, 0);
}

static void draw_lives()
{
    for ( pixel_t x = pac_tiles2pixels(pac_lives * 2); x; x -= pac_tiles2pixels(2) )
        draw_life(x);
}

static void draw()
{
	pac_board_draw();
    draw_lives();

	for (int i = 0; i < PAC_ACTOR_COUNT; ++i)
		(*pac_actors[i].draw)(&pac_actors[i]);
}


//////////////
// Update //
//////////////
static void reset_life(scene_t *scene);

static result_t update_playing(scene_t *scene);
static result_t update_start_life(scene_t *scene);
static result_t update_dying(scene_t *scene);


static void reset_life(scene_t *scene)
{
	pac_actor_pacman_reset(&pac_actors[PAC_ACTOR_PLAYER]);

	for ( size_t i = PAC_GHOST_FIRST; i <= PAC_GHOST_LAST; ++i)
		pac_actor_ghost_reset(&pac_actors[i], (enum pac_actor_e)i);
}

static result_t update_start_life(scene_t *scene)
{
    puts("Start life.\n");
    reset_life(scene);

    scene_timer -= PAC_FRAME_DELAY;
    if ( scene_timer <= 0)
    {
        pac_lives -= 1;
        scene->update = update_playing;
    }

    return PAC_RESULT_NOTHING;
}

static result_t update_dying(scene_t *scene)
{
    puts("TODO: Death animation.\n");

    scene_timer -= PAC_FRAME_DELAY;

    // TODO Do animation

    if ( scene_timer > 0)
        return PAC_RESULT_NOTHING;

    if (!pac_lives)
        return PAC_RESULT_END;

    scene->update = &update_start_life;
    return PAC_RESULT_NOTHING;
}

static result_t update_playing(scene_t *scene)
{
    pac_actor_update();

    unsigned int overlap = actor_overlap(&pac_actors[PAC_ACTOR_PLAYER], &pac_actors[PAC_ACTOR_PLAYER + 1]);
    if (overlap)
    {
        scene_timer = INTRO_TIME;
        scene->update = update_dying;
    }

    return PAC_RESULT_NOTHING;
}

static result_t initialize(scene_t *scene)
{
    pac_board_initialize();
    reset_life(scene);
	pac_lives = 3;
}


/////////////
// Extern //
/////////////

void pac_game_get_scene(scene_t *scene)
{
    memset(scene, 0, sizeof(scene_t));
    
    scene->initialize = &initialize;
    // scene->free = (not needed)

    scene->update = &update_start_life;
    scene->draw = &draw;

    scene->handle_sdl_event = &handle_sdl_event;

    scene_timer = INTRO_TIME;
}