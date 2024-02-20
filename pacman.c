#include "pacman.h"
#include "app.h"
#include <SDL2/SDL_image.h>

static SDL_Texture *pac_tex_load(const char *filename)
{
    SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void pac_pac_create(pacman_t *pacman)
{
    pacman->x = 0;
    pacman->y = 0;

    pacman->texture = pac_tex_load("sanic.png");
}

void pac_pac_draw()
{
}