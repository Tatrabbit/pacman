#include "board.h"
#include "globals.h"
#include "texture.h"
#include <assert.h>

// Auto-generated; see board_data.py
#include "board_data.h"
static wall_t board_state[sizeof board_idx_data];

#define TILED_WALL 0x23
#define INVISIBLE_WALL_INDEX 0xfe
#define EMPTY_INDEX 0xff

static void draw_tile(tex_idx_t *tex_idx, size_t i);

void pac_board_initialize()
{
    for (size_t i = 0; i < sizeof board_idx_data; ++i)
    {
        // Hide all tiles set to invisible wall
        if (board_idx_data[i] == TILED_WALL)
            board_idx_data[i] = INVISIBLE_WALL_INDEX;

        assert(PAC_TILE_EMPTY == 0);
        assert(PAC_TILE_WALL  == 1);
        board_state[i] = (board_idx_data[i] != EMPTY_INDEX);
    }
}

void pac_board_draw()
{
    const tile_t header_height = 3;
    const tile_t footer_height = 2;

    pixel_t start, end;
    start = 0;
    end = PAC_SCREEN_TILES_W * header_height;

    tex_idx_t tex_idx;

    // Header
    tex_idx.palette_idx = 9;

    for (size_t i = start; i < end; ++i)
        draw_tile(&tex_idx, i);

    // Board
    tex_idx.palette_idx = 8;

    start = end;
    end = PAC_SCREEN_TILES_W * (PAC_SCREEN_TILES_H - footer_height);
    for (size_t i = start; i < end; ++i)
        draw_tile(&tex_idx, i);
    
    // TODO - show lives, fruit
    // Footer
    tex_idx.palette_idx = 7;

    start = end;
    end += PAC_SCREEN_TILES_W * footer_height;
    for (int i = start; i < end; ++i)
        draw_tile(&tex_idx, i);
}

wall_t pac_board_kind(const unit_t pos[2])
{
    size_t i, x, y;
    x = (size_t)pos[0] / PAC_UNITS_PER_TILE;
    y = (size_t)pos[1] / PAC_UNITS_PER_TILE;

    i = x + (y * PAC_SCREEN_TILES_W);
    return board_state[i];
}

static void draw_tile(tex_idx_t *tex_idx, size_t i)
{
    tex_idx->tile_idx = board_idx_data[i];
    if (tex_idx->tile_idx >= INVISIBLE_WALL_INDEX)
        return;

    int x, y;
    x = (i % PAC_SCREEN_TILES_W) * PAC_TILE_SIZE;
    y = i / PAC_SCREEN_TILES_W * PAC_TILE_SIZE;

    pac_tex_draw_tile(x, y, tex_idx);
}