#ifndef _TEXTURE_H
#define _TEXTURE_H
/**
 * @file globals.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Represents a texture atlas file.
 * 
 * In general, this should not be used directly by the game itself.
 * Instead, sprites and maps should own or use a texture atlas.
 * 
 * @todo Refactor into a class.
 */

#include <SDL2/SDL.h>

/**
 * @brief Specifies a reference to a tile and palette.
 */
typedef struct
{
    /**
     * @brief Tile index
    */
    unsigned char tile_idx;

    /**
     * @brief Palette index
     */
    unsigned char palette_idx;
} tex_idx_t;

/**
 * @brief Acquire resources.
 * @param[in] data_directory the directory where atlas.png can be found (usually argv[0])
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
 * @param[in] idx tile/palette to use
 */
void pac_tex_draw_sprite(int x, int y, const tex_idx_t *idx);

/**
 * @brief Draw an 8x8 background tile.
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 * @param[in] idx tile/palette to use
 */
void pac_tex_draw_tile(int x, int y, const tex_idx_t *idx);

#endif