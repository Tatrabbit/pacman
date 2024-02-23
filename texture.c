#include "texture.h"
#include "app.h"
#include <SDL2/SDL_image.h>

////////////
// Config //
////////////
#define SHEET_FILENAME "atlas.png"

#define SHEET_PALETTES_W 5
#define SHEET_PALETTES_H 4
#define SHEET_LEFT 1
#define SHEET_TOP 1
#define SHEET_WIDTH 200
#define SHEET_HEIGHT 187

#define SHEET_TILES_W 10
#define PALETTE_LEFT 0u
#define PALETTE_TOP 82u

#define TILE_SIZE 16u
#define TILE_PADDING 1u

SDL_Texture *texture;
const size_t buf_size = 512u;

static void fast_basename(char *path, int length);
static int replace_basename(char *buf, const char *path, const char *new_basename);


/////////////
// Externs //
/////////////

int pac_tex_init(const char *data_directory)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", SHEET_FILENAME);

    char filename[buf_size];
    if (!replace_basename(filename, data_directory, SHEET_FILENAME))
        return 0;

	texture = IMG_LoadTexture(app.renderer, filename);
    if(!texture)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s\n", SDL_GetError());
        return 0;
    }

    SDL_Rect r;
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    if (r.w != 1024 || r.h != 1024)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s must be 1024x1024\n", filename);
        return 0;
    }

    return 1;
}

void pac_tex_cleanup()
{
    if (!texture)
        return;

    SDL_DestroyTexture(texture);
    texture = 0;
}

// The 1 texture atlas has 5x4 sheets
void pac_tex_draw_sprite(int x, int y, tex_idx_t *idx)
{
    const int sheet_count = SHEET_PALETTES_W * SHEET_PALETTES_H;

    // Wrap palette index
    int palette_idx = idx->palette_idx % sheet_count;
    if (palette_idx < 0)
        palette_idx += sheet_count;

    // Which sheet to use
    int sx, sy;
    sx = palette_idx % SHEET_PALETTES_W;
    sy = palette_idx / SHEET_PALETTES_W;

    int tx, ty;
    tx = idx->tile_idx % SHEET_TILES_W;
    ty = idx->tile_idx / SHEET_TILES_W;

    SDL_Rect source, dest;
    // Area = TILE_SIZE
    source.w = source.h = dest.w = dest.h = TILE_SIZE;

    // Destination Position
    dest.x = x;
    dest.y = y;

    // Source Position
    source.x = SHEET_LEFT + (sx * SHEET_WIDTH);
    source.x += (TILE_SIZE + TILE_PADDING) * tx;
    source.x += PALETTE_LEFT;

    source.y = SHEET_TOP + (sy * SHEET_HEIGHT);
    source.y += (TILE_SIZE + TILE_PADDING) * ty;
    source.y += PALETTE_TOP;

	SDL_RenderCopy(app.renderer, texture, &source, &dest);
}


////////////
// Static //
////////////

/**
 * @brief similar to basename()
 * @param length strlen(path)
 * 
 * @todo Windows support
 */
static void fast_basename(char *path, int length)
{
    // Iterate backwards and terminate after the /
    char *name = path + length;

    while (name >= path)
    {
        char c = *(name--);
        if (c == '/')
        {
            *(name + 2) = '\0';
            return;
        }
    }
}

/**
 * @brief Replace the basename of a path
 * 
 * @param buf temporary char array to use
 * @param path the path to replace the basename of
 * @param new_basename The new basename to use
 * @return non-zero on success
 */
static int replace_basename(char *buf, const char *path, const char *new_basename)
{
    int idx = strlen(path);
    if(idx >= buf_size)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", "Filename length error");
        return 0;
    }

    strcpy(buf, path);
    fast_basename(buf, idx);
    strncat(buf, new_basename, buf_size);

    return 1;
}