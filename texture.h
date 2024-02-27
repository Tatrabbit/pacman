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
 */

#include <SDL2/SDL.h>

/**
 * @brief Texture atlas
 * 
 * Responsible for the ownership and lifetime of SDL_Texture
 */
typedef struct atlas_s
{
    /**
     * @brief The managed texture
     */
    SDL_Texture *texture;
} atlas_t;

/**
 * @brief Specifies a reference to a tile and palette.
 */
typedef struct
{
    /**
     * @brief Pointer to the associated atlas.
     */
    const atlas_t *atlas_ref;

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
 * @memberof atlas_s
 * @brief Initialize from an image file.
 * @param[in] filename Filename of texture image
 * @return non-zero on success, 0 on failure
 */
int pac_atlas_init_image(atlas_t *, const char *filename);

/**
 * @memberof atlas_s
 * @brief Free resources.
 */
void pac_atlas_destroy(atlas_t *);

/**
 * @memberof tex_idx_t
 * @brief Draw a 16x16 character sprite.
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 */
void pac_tex_draw_sprite(const tex_idx_t *, int x, int y);

/**
 * @memberof tex_idx_t
 * @brief Draw an 8x8 background tile.
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 */
void pac_tex_draw_tile(const tex_idx_t *, int x, int y);

#endif