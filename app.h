#ifndef _APP_H
#define _APP_H
/**
 * @file app.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Interface to system-wide utilities.
 */

#include <SDL2/SDL.h>

/**
 * @brief System-wide toolbox.
 */
struct app_s
{
	/**
	 * @brief The main game window.
	 */
	SDL_Window *window;

	/**
	 * @brief The primary renderer.
	 */
	SDL_Renderer *renderer;
};

/**
 * @brief Singleton defined in app.c
 */
#ifndef _APP_C
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

#endif