#ifndef _BOARD_H
#define _BOARD_H
/**
 * @file board.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief Implements the game board, including map collision.
 * @todo The board should be implemented as a class.
 */

#include "texture.h"
#include "globals.h"

/**
 * @brief Represents the current state of a tile on the board.
 * 
 * This is stored a bitmask.
 * @note PAC_TILE_EMPTY will always be 0,
 *       and PAC_TILE_WALL will always be 1.
 *       This allows checking if a tile is empty with the ! operator
 */
typedef enum {
    PAC_TILE_EMPTY  = 0x0,
    PAC_TILE_WALL   = 0x1,

    PAC_TILE_DOT    = 0x2,
    PAC_TILE_PELLET = 0x4,
    PAC_TILE_EATEN  = 0x8,
    PAC_TILE_NO_UP  = 0x10,

} wall_t;

/**
 * @brief Resets the board for the next level.
 * 
 * It replaces the dots and power pellets.
 */
void pac_board_reset();

/**
 * @brief Constructor.
 * 
 * The board will be begin in a new-level state,
 * as if `pac_board_reset` had been called.
 * @sa pac_board_reset
 * 
 * @param[in] atlas Existing atlas to use when drawing.
 */
void pac_board_initialize(const atlas_t *atlas);

/**
 * @brief Draw the board.
 */
void pac_board_draw();

/**
 * @brief Check the kind of tile.
 * @param[in] pos Position of the tile to check.
 * @todo Please encapsulate.
 */
wall_t pac_board_kind_unit(const unit_t pos[2]);

/**
 * @brief Check the kind of tile.
 * @param[in] pos Position of the tile to check.
 * @todo Please encapsulate.
 * @overload
 */
wall_t pac_board_kind_tile(const unit_t pos[2]);

/**
 * @brief Remove a pellet from this board.
 * 
 * If the pellet was already eaten, does nothing.
 * 
 * @param[in] pos Position of the pellet.
 * @return Returns the wall type corresponding to the pellet removed, or `PAC_TILE_EMPTY`
 *         if there were no changes.
 */
wall_t pac_board_eat(const unit_t pos[2]);

#endif