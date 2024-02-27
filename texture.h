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
     * @private
     */
    SDL_Texture *_texture;

    /**
     * @brief Width, in pixels, of one palette's sheet
     */
    unsigned short sheet_width;


    /**
     * @brief Height, in pixels, of one palette's sheet
     */
    unsigned short sheet_height;

    /**
     * @brief X and Y size of one tile.
     */
    unsigned char tile_size;


    /**
     * @brief Unused margin on the left-most edge of the texture
     */
    unsigned char margin_x;
    
    /**
     * @brief Unused margin on the top-most edge of the texture
     */
    unsigned char margin_y;


     /**
     * @brief Unused margin on the left-most edge of each palette's sheet
     */
    unsigned char sheet_padding_x;

    /**
     * @brief Unused margin on the top-most edge of each palette's sheet
     */
    unsigned char sheet_padding_y;


    /**
     * @brief Horizontal padding between each tile
     */
    unsigned char tile_padding_x;

    /**
     * @brief Vertical padding between each tile
     */
    unsigned char tile_padding_y;

    /**
     * @brief The number of sheets in each column
     */
    unsigned char n_sheets_w;

    /**
     * @brief The number of sheets in each row
     */
    unsigned char n_sheets_h;

    /**
     * @brief The number of tiles per row in one sheet
     */
    unsigned char n_tiles_w;

    /**
     * @private
     */
    unsigned char _has_ownership;
    
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
 * @param[in,out] self This atlas
 * @param[in] filename Filename of texture image
 * @return non-zero on success, 0 on failure
 * 
 * @note In order to check the dimensions of the loaded image and ensure they're
 * acceptable, all public value of @p self must be fully set.
 */
int pac_atlas_init_image(atlas_t *self, const char *filename);

/**
 * @memberof atlas_s
 * @brief Initialize from another atlas.
 * @param[in] other Existing atlas to clone.
 */
void pac_atlas_init_atlas(atlas_t *, const atlas_t *other);

/**
 * @memberof atlas_s
 * @brief Free resources.
 */
void pac_atlas_destroy(atlas_t *);

/**
 * @memberof tex_idx_t
 * @brief Draw the specified tile from a texture atlas
 * @param x X Position, in pixels
 * @param y Y Position, in pixels
 */
void pac_tile_draw(const tex_idx_t *, int x, int y);

#endif