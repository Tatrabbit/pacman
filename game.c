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

static unsigned char pac_lives;


static result_t handle_sdl_event(SDL_Event *evt)
{
	switch (evt->type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pac_actor_pacman_handle_keyboard(&pac_actors[PAC_ACTOR_PLAYER], evt);
	}

    return _NOTHING;
}

static void draw()
{
	pac_board_draw();

	for (int i = 0; i < PAC_ACTOR_COUNT; ++i)
		(*pac_actors[i].draw)(&pac_actors[i]);
}

static void update()
{
    pac_actor_update();
}

static result_t initialize(scene_t *scene)
{
    // TODO game Init:
	pac_board_initialize();
	pac_actor_pacman_initialize(&pac_actors[PAC_ACTOR_PLAYER]);

	for ( size_t i = PAC_GHOST_FIRST; i <= PAC_GHOST_LAST; ++i)
		pac_actor_ghost_initialize(&pac_actors[i], (enum pac_actor_e)i);

	pac_lives = 3;
}


/////////////
// Extern //
/////////////

void pac_game_get_scene(scene_t *scene)
{
    memset(scene, 0, sizeof(scene_t));
    
    scene->initialize = &initialize;
    scene->update = &update;
    scene->draw = &draw;

    scene->handle_sdl_event = &handle_sdl_event;
}