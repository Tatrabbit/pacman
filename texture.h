#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>

typedef struct
{
    char tile_idx;
    char palette_idx; 
} tex_idx_t;

int pac_tex_init(const char *data_directory);
void pac_tex_cleanup();

void pac_tex_draw_sprite(int x, int y, tex_idx_t *idx);

#endif