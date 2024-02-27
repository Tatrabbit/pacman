#include "globals.h"
#include <SDL2/SDL.h>

pixel_t pac_units2pixels(unit_t units)
{
    pixel_t value = ((pixel_t)units) * PAC_TILE_SIZE;
    value /= PAC_UNITS_PER_TILE;
    return value;
}

int replace_basename(char buf[PAC_STR_BUF_SIZE], const char *path, const char *new_basename)
{
    size_t basename_length, length = strlen(path);
    if(length >= PAC_STR_BUF_SIZE)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", "Filename length error");
        return 0;
    }

    memcpy(buf, path, length + 1);
    basename_length = trim_basename_fast(buf, length);
    memcpy(buf + (length - basename_length) + 1, new_basename, length);
    return 1;
}

size_t trim_basename_fast(char *path, int length)
{
    // Iterate backwards and terminate after the /
    char *name = path + length;

    size_t basename_length = 0;
    while (name >= path)
    {
        char c = *(name--);
        if (c == '/')
        {
            *(name + 2) = '\0';
            return basename_length;
        }

        basename_length += 1;
    }

    return 0;
}