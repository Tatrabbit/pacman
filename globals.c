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
    size_t path_length = strlen(path);
    size_t basename_length = strlen(new_basename);

    if(path_length >= PAC_STR_BUF_SIZE)
        goto length_error;

    if ( path_length == 0)
    {
        if(basename_length >= PAC_STR_BUF_SIZE)
            goto length_error;

        memcpy(buf, new_basename, basename_length + 1);
    }
    else
        memcpy(buf, path, path_length + 1);

    char *last_sep = strrchr(buf, '/');
    if (!last_sep)
        last_sep = buf;

    size_t new_length = (last_sep - buf);
    buf[new_length] = '/';

    if ((new_length + basename_length) >= PAC_STR_BUF_SIZE)
        goto length_error;

    memcpy(buf + new_length + 1, new_basename, basename_length + 1);
    return 1;

length_error:
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", "Filename length error");
    return 0;
}