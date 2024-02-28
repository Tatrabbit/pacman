#include "texture.h"
#include "app.h"
#include "globals.h"
#include <SDL2/SDL_image.h>


/////////////
// Externs //
/////////////

int pac_atlas_init_image(atlas_t *self, const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	self->_texture = IMG_LoadTexture(app.renderer, filename);
    if(!self->_texture)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return 0;
    }

    self->_has_ownership = 1;

    int required_width = (self->sheet_width + self->sheet_padding_x) * self->n_sheets_w + self->margin_x;
    int required_height = (self->sheet_height + self->sheet_padding_y) * self->n_sheets_h + self->margin_x;

    SDL_Rect r;
	SDL_QueryTexture(self->_texture, NULL, NULL, &r.w, &r.h);
    if (r.w < required_width || r.h < required_height)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s must be >= %dx%d\n", filename, required_width, required_height);
        return 0;
    }

    return 1;
}

void pac_atlas_init_atlas(atlas_t *self, const atlas_t *other)
{
    memcpy(self, other, sizeof(atlas_t));
    self->_has_ownership = 0;
}

void pac_atlas_destroy(atlas_t *atlas)
{
    if (!atlas->_texture)
        return;

    if (!atlas->_has_ownership)
        return;

    SDL_DestroyTexture(atlas->_texture);
    atlas->_texture = 0;
}


void pac_atlas_draw_tile(const atlas_t *self, unsigned char tile, unsigned char pallete, pixel_t x, pixel_t y, int flip_state)
{
    const int sheet_count = self->n_sheets_w * self->n_sheets_h;
    const int tile_size = self->tile_size;

    // Wrap palette index
    int palette_idx = pallete % sheet_count;
    if (palette_idx < 0)
        palette_idx += sheet_count;

    // Which sheet to use
    int sx, sy;
    sx = palette_idx % self->n_sheets_w;
    sy = palette_idx / self->n_sheets_w;

    int tx, ty;
    tx = tile % self->n_tiles_w;
    ty = tile / self->n_tiles_w;

    SDL_Rect source, dest;
    // Area = PAC_TILE_SIZE
    source.w = source.h = dest.w = dest.h = tile_size;

    // Destination Position
    dest.x = x;
    dest.y = y;

    // Source Position
    source.x = self->margin_x + (sx * self->sheet_width);
    source.x += (tile_size + self->tile_padding_x) * tx;

    source.y = self->margin_y + (sy * self->sheet_height);
    source.y += (tile_size + self->tile_padding_y) * ty;

    SDL_RenderCopyEx(app.renderer, self->_texture, &source, &dest, 0.0, NULL, flip_state);
}