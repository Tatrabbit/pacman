#include "sprite.h"
#include "app.h"
#include "texture.h"
#include "defines.h"

static sprite_t sprites[5];
#define pacman (sprites[0])
// TODO ghosts

static const unsigned char pacman_anim_h[] = {39, 50};

static void draw_one(sprite_t *sprite);

// Space conversions
#define tiles(x) (x * PAC_UNITS_PER_TILE)
static int pixels_x(int units);
static int pixels_y(int units);

void pac_sprite_initialize()
{
    memset(&pacman, 0, sizeof(sprite_t));

	pacman.tex_idx.tile_idx = 61;
	pacman.tex_idx.palette_idx = 7;

    pacman.x = tiles(13);
    pacman.y = tiles(16);
}

void pac_sprite_draw_all()
{
    draw_one(&pacman);
}

static void draw_one(sprite_t *sprite)
{
    int x, y;
    x = pixels_x(sprite->x);
    y = pixels_y(sprite->y);

    pac_tex_draw_sprite(x, y, (tex_idx_t *)sprite);
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