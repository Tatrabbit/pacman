#ifndef _DEFINES_H
#define _DEFINES_H

#include <stddef.h>

#define PAC_SCREEN_TILES_W 28
#define PAC_SCREEN_TILES_H 36

#define PAC_TILE_SIZE 8
#define PAC_UNITS_PER_TILE 800

typedef int pixel_t;
typedef unsigned short tile_t;
typedef unsigned short unit_t;

/**
 * @brief Converts units to pixels in place.
 * @param units array[2] of x,y
 */
// void pac_units2pixels(unit_t units[2]);

#define pac_tiles2units(x) ((unit_t)((x) * PAC_UNITS_PER_TILE))

/**
 * @brief Converts units to pixels.
 * 
 * This function will call either @see spac_units2pixels_x or @see pac_units2pixels_y.
 * @param units array[2] of x,y
 * @param axis 0 or 1 (index of array)
 * @return pixels
 */
pixel_t pac_units2pixels(const unit_t units[2], size_t axis);


/**
 * @brief Converts units to pixels.
 * 
 * @param units value in unit space.
 * @return value in pixel space.
 */
pixel_t pac_units2pixels_x(unit_t units);

/**
 * @brief Converts units to pixels.
 * 
 * @param units value in unit space.
 * @return value in pixel space.
 */
pixel_t pac_units2pixels_y(unit_t units);


#endif