#define _GLOBALS_C
#include "globals.h"
#include <SDL2/SDL_image.h>

const int init_flags = (SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO);

int pac_app_init()
{
    if (SDL_Init(init_flags) != 0)
    {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

	IMG_Init(IMG_INIT_PNG);

    int size_x, size_y;
    size_x = PAC_SCREEN_TILES_W * PAC_TILE_SIZE;
    size_y = PAC_SCREEN_TILES_H * PAC_TILE_SIZE;

    app.window = SDL_CreateWindow("Pac-Man",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    size_x, size_y, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    app.renderer = SDL_CreateRenderer(app.window, -1, render_flags);
    return 0;
}

void pac_app_cleanup()
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

pixel_t pac_units2pixels(unit_t units)
{
    pixel_t value = ((pixel_t)units) * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;
    return value;
}

int replace_basename(char buf[PAC_STR_BUF_SIZE], const char *path, const char *new_basename)
{
    size_t path_length = strlen(path);
    size_t basename_length = strlen(new_basename);

    if(path_length >= PAC_STR_BUF_SIZE)
        goto length_error;

    if ( path_length == 0)
    {
        if(basename_length >= PAC_STR_BUF_SIZE)
            goto length_error;

        memcpy(buf, new_basename, basename_length + 1);
    }
    else
        memcpy(buf, path, path_length + 1);

    char *last_sep = strrchr(buf, '/');
    if (!last_sep)
        last_sep = buf;

    size_t new_length = (last_sep - buf);
    buf[new_length] = '/';

    if ((new_length + basename_length) >= PAC_STR_BUF_SIZE)
        goto length_error;

    memcpy(buf + new_length + 1, new_basename, basename_length + 1);
    return 1;

length_error:
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", "Filename length error");
    return 0;
}