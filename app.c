#define _APP_C
#include "app.h"
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

    app.window = SDL_CreateWindow("GAME",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    500, 500, 0);

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