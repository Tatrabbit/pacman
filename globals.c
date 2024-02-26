#include "globals.h"

inline static pixel_t units2pixels_nooffset(unit_t units);


pixel_t pac_units2pixels(unit_t units)
{
    pixel_t value = ((pixel_t)units) * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;
    return value;
}