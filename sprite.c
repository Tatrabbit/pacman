#include "sprite.h"
#include "app.h"
#include "texture.h"
#include "globals.h"


void pac_sprite_draw(const sprite_t *sprite)
{
    int x, y;
    x = pac_units2pixels(sprite->pos[0]);
    y = pac_units2pixels(sprite->pos[1]);
    // TODO offset

    pac_tex_draw_sprite(x, y, (tex_idx_t *)sprite);
}