#include "texture.h"
#include "app.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

////////////
// Config //
////////////

#define SHEET_PALETTES_W 5
#define SHEET_PALETTES_H 4
#define SHEET_LEFT 1
#define SHEET_TOP 1
#define SHEET_WIDTH 200
#define SHEET_HEIGHT 186

#define SHEET_TILES_W 22u

#define SPRITE_TOP 82u
#define TILE_PADDING 1u


/////////////
// Externs //
/////////////

int pac_atlas_init_image(atlas_t *self, const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	self->texture = IMG_LoadTexture(app.renderer, filename);
    if(!self->texture)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return 0;
    }

    SDL_Rect r;
	SDL_QueryTexture(self->texture, NULL, NULL, &r.w, &r.h);
    if (r.w != 1024 || r.h != 1024)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s must be 1024x1024\n", filename);
        return 0;
    }

    return 1;
}

void pac_atlas_destroy(atlas_t *atlas)
{
    if (!atlas->texture)
        return;

    SDL_DestroyTexture(atlas->texture);
    atlas->texture = 0;
}

static void draw_shared(int x, int y, const tex_idx_t *idx, int tile_scale, int yoffset)
{
    const int sheet_count = SHEET_PALETTES_W * SHEET_PALETTES_H;
    const int tile_size = PAC_TILE_SIZE * tile_scale;

    // Wrap palette index
    int palette_idx = idx->palette_idx % sheet_count;
    if (palette_idx < 0)
        palette_idx += sheet_count;

    // Which sheet to use
    int sx, sy;
    sx = palette_idx % SHEET_PALETTES_W;
    sy = palette_idx / SHEET_PALETTES_W;

    int tx, ty;
    tx = idx->tile_idx % (SHEET_TILES_W / tile_scale);
    ty = idx->tile_idx / (SHEET_TILES_W / tile_scale);

    SDL_Rect source, dest;
    // Area = PAC_TILE_SIZE
    source.w = source.h = dest.w = dest.h = tile_size;

    // Destination Position
    dest.x = x;
    dest.y = y;

    // Source Position
    source.x = SHEET_LEFT + (sx * SHEET_WIDTH);
    source.x += (tile_size + TILE_PADDING) * tx;

    source.y = SHEET_TOP + (sy * SHEET_HEIGHT);
    source.y += (tile_size + TILE_PADDING) * ty;
    source.y += yoffset;

	SDL_RenderCopy(app.renderer, idx->atlas_ref->texture, &source, &dest);
}

void pac_tex_draw_sprite(const tex_idx_t *idx, pixel_t x, pixel_t y)
{
    // TODO my 1 texture atlas has 5x4 sheets.
    // These two functions should be changed, so that the atlas knows its offset.
    draw_shared(x, y, idx, 2u, SPRITE_TOP);
}

void pac_tex_draw_tile(const tex_idx_t *idx, pixel_t x, pixel_t y)
{
    draw_shared(x, y, idx, 1u, 0u);
}