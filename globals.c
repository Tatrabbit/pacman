#include "globals.h"

inline static pixel_t units2pixels_nooffset(unit_t units);


pixel_t pac_units2pixels(const unit_t units[2], size_t axis)
{
    if (axis == 0)
        return pac_units2pixels_x(units[0]);
    else
        return pac_units2pixels_y(units[axis]);
}

pixel_t pac_units2pixels_x(unit_t units)
{
    pixel_t value = units2pixels_nooffset(units);
    value += (PAC_TILE_SIZE * 1);
    value += PAC_TILE_SIZE / -2;
    return value;
}

pixel_t pac_units2pixels_y(unit_t units)
{
    pixel_t value = units2pixels_nooffset(units);
    value += (PAC_TILE_SIZE * 4);
    value += PAC_TILE_SIZE / -2;
    return value;
}

inline static pixel_t units2pixels_nooffset(unit_t units)
{
    pixel_t value = ((pixel_t)units) * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;
    return value;
}