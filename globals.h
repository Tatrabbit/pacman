#ifndef _GLOBALS_H
#define _GLOBALS_H
/**
 * @file globals.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief application-wide defines and typedefs, and helper utilities for them.
 */


#include <stddef.h>

/**
 * @brief Horizontal screen size, in tiles.
*/
#define PAC_SCREEN_TILES_W 28

/**
 * @brief Vertical screen size, in tiles.
*/
#define PAC_SCREEN_TILES_H 36

/**
 * @brief Number of pixels in each dimension of a tile.
 */
#define PAC_TILE_SIZE 8

/**
 * @brief Defines scale of Pac Units.
 * 
 * A @ref unit_t must be large enough to safely contain the bottom, right most unit of the screen, plus 2 more tiles.
 */
#define PAC_UNITS_PER_TILE 800

/**
 * @brief Size of temporary string buffers.
*/
#define PAC_STR_BUF_SIZE ((size_t)512u)

/**
 * @brief Signed integer representing whole pixels.
 */
typedef int pixel_t;

/**
 * @brief Integer representing tiles.
 */
typedef unsigned short tile_t;

/**
 * @brief Integer representing Pac Units.
 */
typedef unsigned short unit_t;

/**
 * @brief Converts tile space to unit space.
 * @param x Value in tile space.
 * @return unit_t 
*/
#define pac_tiles2units(x) ((unit_t)(x) * PAC_UNITS_PER_TILE)

/**
 * @brief Converts tile space to pixel space.
 * @param x Value in tile space.
 * @return pixel_t
*/
#define pac_tiles2pixels(x) ((pixel_t)(x) * PAC_TILE_SIZE)

/**
 * @brief Converts units to pixels.
 * 
 * @param units value in unit space.
 * @return value in pixel space.
 */
pixel_t pac_units2pixels(unit_t units);


/**
 * @brief Replace the basename of a path
 * @note \p buf must be at least `PAC_STR_BUF_SIZE` to avoid buffer overflow
 * 
 * @param[out] buf An existing buffer to store the result
 * @param[in] path The filesystem path to replace the basename of
 * @param[in] new_basename The new basename to use
 * @return non-zero on success
 */
int replace_basename(char buf[PAC_STR_BUF_SIZE], const char *path, const char *new_basename);


#endif