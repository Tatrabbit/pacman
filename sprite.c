#include "sprite.h"
#include "app.h"
#include "texture.h"
#include "globals.h"


void pac_sprite_draw(const sprite_t *sprite)
{
    int x, y;
    x = pac_units2pixels_x(sprite->pos[0]);
    y = pac_units2pixels_y(sprite->pos[1]);

    pac_tex_draw_sprite(x, y, (tex_idx_t *)sprite);
}