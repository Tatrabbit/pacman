#ifndef _BOARD_H
#define _BOARD_H

#include "globals.h"

typedef enum {
    PAC_TILE_EMPTY = 0b0000, // MUST BE 0!
    PAC_TILE_WALL  = 0b0001, // MUST BE 1! (see board.c)
    PAC_TILE_DOT   = 0b0010,
} wall_t;

void pac_board_initialize();
void pac_board_draw();

wall_t pac_board_kind(const unit_t pos[2]);

#endif