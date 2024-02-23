#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>

typedef struct
{
    unsigned char tile_idx;
    unsigned char palette_idx; 
} tex_idx_t;

/**
 * @brief Acquire resources.
 * @param data_directory the directory where atlas.png can be found (usually argv[0])
 * @return non-zero on success, 0 on failure
 */
int pac_tex_init(const char *data_directory);

/**
 * @brief Free resources.
 */
void pac_tex_cleanup();

/**
 * @brief Draw a 16x16 character sprite.
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 * @param idx tile/palette to use
 */
void pac_tex_draw_sprite(int x, int y, tex_idx_t *idx);

/**
 * @brief Draw an 8x8 background tile.
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 * @param idx tile/palette to use
 */
void pac_tex_draw_tile(int x, int y, tex_idx_t *idx);

#endif