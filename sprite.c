#include "sprite.h"
#include "app.h"
#include "texture.h"
#include "defines.h"

// Space conversions
static int pixels_x(int units);
static int pixels_y(int units);


void pac_sprite_draw(const sprite_t *sprite)
{
    int x, y;
    x = pixels_x(sprite->x);
    y = pixels_y(sprite->y);

    pac_tex_draw_sprite(x, y, (tex_idx_t *)sprite);
}

void pac_sprite_set_pos(sprite_t *sprite, unsigned short x, unsigned short y)
{
    sprite->x = x * PAC_UNITS_PER_TILE;
    sprite->y = y * PAC_UNITS_PER_TILE;
}


static int pixels_x(int units)
{
    int value = units * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;

    value += (PAC_TILE_SIZE * 1);
    value += PAC_TILE_SIZE / -2;

    return value;
}

static int pixels_y(int units)
{
    int value = units * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;

    value += (PAC_TILE_SIZE * 4);
    value += PAC_TILE_SIZE / -2;
    
    return value;
}