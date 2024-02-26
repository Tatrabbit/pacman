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

#define pac_tiles2units(x) ((unit_t)((x) * PAC_UNITS_PER_TILE))

/**
 * @brief Converts units to pixels.
 * 
 * @param units value in unit space.
 * @return value in pixel space.
 */
pixel_t pac_units2pixels(unit_t units);


#endif