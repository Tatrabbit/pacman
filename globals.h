#ifndef _GLOBALS_H
#define _GLOBALS_H
/**
 * @file globals.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief application-wide defines and typedefs, and helper utilities for them.
 */
#include <stddef.h>
#include <SDL2/SDL.h>

/**
 * @brief Horizontal screen size, in tiles.
*/
#define PAC_SCREEN_TILES_W 28

/**
 * @brief Vertical screen size, in tiles.
*/
#define PAC_SCREEN_TILES_H 36

/**
 * @brief Number of pixels in each dimension of a tile.
 */
#define PAC_TILE_SIZE 8

/**
 * @brief Defines scale of Pac Units.
 * 
 * A @ref unit_t must be large enough to safely contain the bottom, right most unit of the screen, plus 2 more tiles.
 */
#define PAC_UNITS_PER_TILE 800

/**
 * @brief Size of temporary string buffers.
*/
#define PAC_STR_BUF_SIZE ((size_t)512u)

struct atlas_s;

/**
 * @brief System-wide toolbox.
 */
struct app_s
{
    int argc;
    const char **argv;

	/**
	 * @brief The main game window.
	 */
	SDL_Window *window;

	/**
	 * @brief The primary renderer.
	 */
	SDL_Renderer *renderer;

    struct atlas_s *tile_atlas;
    struct atlas_s *sprite_atlas;
};

typedef enum
{
	_NOTHING = 0x0,
	_QUIT = 0x1,
	_FRAME = 0x2,

	_ERROR = -1
} result_t;

typedef struct scene_s
{
    result_t (*initialize)(struct scene_s *);
    result_t (*free)(struct scene_s *);

    result_t (*handle_sdl_event)(SDL_Event *);
    result_t (*handle_user_event)(SDL_Event *);

    void (*update)(struct scene_s *);
    void (*draw)(struct scene_s *);

    void *data;
} scene_t;

/**
 * @brief Singleton defined in globals.c
 */
#ifndef _GLOBALS_C
extern
#endif
struct app_s app;

/**
 * @static @memberof app_s
 * @brief Acquire resources.
 * @return Non-zero on success.
 */
int pac_app_init();

/**
 * @static @memberof app_s
 * @brief free resources.
 */
void pac_app_cleanup();

/**
 * @brief Signed integer representing whole pixels.
 */
typedef int pixel_t;

/**
 * @brief Integer representing tiles.
 */
typedef unsigned short tile_t;

/**
 * @brief Integer representing Pac Units.
 * @todo refactor. Use only for storage, unsigned char.
 */
typedef unsigned short unit_t;

/**
 * @brief Converts tile space to unit space.
 * @param x Value in tile space.
 * @return unit_t 
*/
#define pac_tiles2units(x) ((unit_t)(x) * PAC_UNITS_PER_TILE)

/**
 * @brief Converts tile space to pixel space.
 * @param x Value in tile space.
 * @return pixel_t
*/
#define pac_tiles2pixels(x) ((pixel_t)(x) * PAC_TILE_SIZE)

/**
 * @brief Converts units to pixels.
 * 
 * @param units value in unit space.
 * @return value in pixel space.
 */
pixel_t pac_units2pixels(unit_t units);


/**
 * @brief Replace the basename of a path
 * @note \p buf must be at least `PAC_STR_BUF_SIZE` to avoid buffer overflow
 * 
 * @param[out] buf An existing buffer to store the result
 * @param[in] path The filesystem path to replace the basename of
 * @param[in] new_basename The new basename to use
 * @return non-zero on success
 */
int replace_basename(char buf[PAC_STR_BUF_SIZE], const char *path, const char *new_basename);


#endif