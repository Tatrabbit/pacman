#include <SDL2/SDL.h>

typedef struct
{
    int x;
    int y;
    SDL_Texture *texture;
} pacman_t;

void pac_pac_create(pacman_t *pacman);