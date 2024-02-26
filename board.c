#include "board.h"
#include "globals.h"
#include "texture.h"

// Auto-generated; see board_data.py
#include "board_data.h"

static void draw_tile(tex_idx_t *tex_idx, int i)
{
    tex_idx->tile_idx = board_idx_data[i];
    if (tex_idx->tile_idx == 0xff)
        return;

    int x, y;
    x = (i % PAC_SCREEN_TILES_W) * PAC_TILE_SIZE;
    y = i / PAC_SCREEN_TILES_W * PAC_TILE_SIZE;

    pac_tex_draw_tile(x, y, tex_idx);
}

void pac_board_draw()
{
    const int header_height = 3;
    const int footer_height = 2;

    int start, end;
    start = 0;
    end = PAC_SCREEN_TILES_W * header_height;

    tex_idx_t tex_idx;

    // Header
    tex_idx.palette_idx = 9;

    for (int i = start; i < end; ++i)
        draw_tile(&tex_idx, i);

    // Board
    tex_idx.palette_idx = 8;

    start = end;
    end = PAC_SCREEN_TILES_W * (PAC_SCREEN_TILES_H - footer_height);
    for (int i = start; i < end; ++i)
        draw_tile(&tex_idx, i);
    
    // TODO - show lives, fruit
    // Footer
    tex_idx.palette_idx = 7;

    start = end;
    end += PAC_SCREEN_TILES_W * footer_height;
    for (int i = start; i < end; ++i)
        draw_tile(&tex_idx, i);
}