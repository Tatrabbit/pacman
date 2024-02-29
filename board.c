#include "board.h"
#include <assert.h>

// Auto-generated; see board_data.py
#include "board_data.h"
static wall_t board_state[sizeof board_idx_data];
static const atlas_t *atlas_ref;

#define TILED_INVISIBLE_WALL 0x23
#define TILED_DOT 0x25
#define TILED_PELLET 0x51

#define INVISIBLE_WALL_INDEX 0xfe
#define EMPTY_INDEX 0xff

static void draw_tile(size_t i, size_t tile, unsigned char palette);

void pac_board_initialize(const atlas_t *atlas)
{
    assert(PAC_TILE_EMPTY == 0);
    assert(PAC_TILE_WALL  == 1);

    atlas_ref = atlas;

    for (size_t i = 0; i < sizeof board_idx_data; ++i)
    {
        // Hide all tiles set to invisible wall
        switch(board_idx_data[i])
        {
        case TILED_INVISIBLE_WALL:
            board_idx_data[i] = INVISIBLE_WALL_INDEX;
            board_state[i] = PAC_TILE_WALL;
            break;

        case TILED_DOT:
            board_idx_data[i] = EMPTY_INDEX;
            board_state[i] = PAC_TILE_DOT;
            break;

        case TILED_PELLET:
            board_idx_data[i] = EMPTY_INDEX;
            board_state[i] = PAC_TILE_PELLET;
            break;

        default:
            board_state[i] = (board_idx_data[i] != EMPTY_INDEX);
        }   
    }
}

void pac_board_reset()
{
    for (size_t i = 0; i < sizeof board_idx_data; ++i)
        board_state[i] &= (0xff ^ PAC_TILE_EATEN);
}

void pac_board_draw()
{
    const tile_t header_height = 3;
    const tile_t footer_height = 2;

    pixel_t start, end;
    start = 0;
    end = PAC_SCREEN_TILES_W * header_height;

    // Header
 

    for (size_t i = start; i < end; ++i)
        draw_tile(i, board_idx_data[i], 9);

    // Board
    start = end;
    end = PAC_SCREEN_TILES_W * (PAC_SCREEN_TILES_H - footer_height);
    for (size_t i = start; i < end; ++i)
    {
        size_t tile = board_idx_data[i];
        int pellet = (board_state[i] & (PAC_TILE_DOT | PAC_TILE_PELLET));

        if (pellet && !(board_state[i] & PAC_TILE_EATEN))
            tile = (pellet == PAC_TILE_DOT) ? TILED_DOT : TILED_PELLET;

        draw_tile(i, tile, 8);
    }
    
    // TODO - show lives, fruit
    // Footer
    start = end;
    end += PAC_SCREEN_TILES_W * footer_height;
    for (size_t i = start; i < end; ++i)
        draw_tile(i, board_idx_data[i], 7);
}

wall_t pac_board_kind(const unit_t pos[2])
{
    size_t i, x, y;
    x = (size_t)pos[0] / PAC_UNITS_PER_TILE;
    y = (size_t)pos[1] / PAC_UNITS_PER_TILE;

    i = x + (y * PAC_SCREEN_TILES_W);
    return board_state[i];
}

wall_t pac_board_eat(const unit_t pos[2])
{
    size_t i, x, y;
    x = (size_t)pos[0] / PAC_UNITS_PER_TILE;
    y = (size_t)pos[1] / PAC_UNITS_PER_TILE;

    i = x + (y * PAC_SCREEN_TILES_W);

    if (board_state[i] & PAC_TILE_EATEN)
        return PAC_TILE_EMPTY;

    int type_eaten = board_state[i] & (PAC_TILE_PELLET | PAC_TILE_DOT);

    if (!type_eaten)
        return PAC_TILE_EMPTY;

    board_state[i] |= PAC_TILE_EATEN;
    return type_eaten;
}

static void draw_tile(size_t i, size_t tile, const unsigned char palette)
{
    if (tile >= INVISIBLE_WALL_INDEX)
        return;

    int x, y;
    x = (i % PAC_SCREEN_TILES_W) * PAC_TILE_SIZE;
    y = i / PAC_SCREEN_TILES_W * PAC_TILE_SIZE;

    pac_atlas_draw_tile(atlas_ref, tile, palette, x, y, 0);
}