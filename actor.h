#ifndef _ACTOR_H
#define _ACTOR_H
/**
 * @file actor.h
 * @copyright MIT License. Full details are in the `LICENSE` file in the project's root directory.
 * 
 * @brief A generic character in the game.
 * @todo move direction stuff to globals.h
 */

#include "texture.h"
#include "globals.h"

enum pac_actor_e {
    PAC_ACTOR_PLAYER = 0,

    PAC_ACTOR_BLINKY = 1,

    // TODO
    // PAC_ACTOR_PINKY,
    // PAC_ACTOR_INKY,
    // PAC_ACTOR_CLYDE,

    PAC_ACTOR_COUNT
};

#define PAC_GHOST_FIRST PAC_ACTOR_BLINKY
#define PAC_GHOST_LAST (PAC_ACTOR_COUNT - 1)

/**
 * @brief Current frame of the animation.
 * 
 * Whole frames are in `PAC_UNITS_PER_TILE`.
 * @sa PAC_UNITS_PER_TILE
 */
#ifndef _ACTOR_C
extern
#endif

unit_t pac_actor_anim_frame;

/**
 * @brief Directional bitmask.
 */
enum pac_direction_e
{
    PAC_DIRECTION_NONE = 0b0000,

    PAC_DIRECTION_RIGHT = 0b0001,
    PAC_DIRECTION_DOWN  = 0b0010,
    PAC_DIRECTION_LEFT  = 0b0100,
    PAC_DIRECTION_UP    = 0b1000,

    PAC_DIRECTION_HORIZONTAL = (PAC_DIRECTION_LEFT | PAC_DIRECTION_RIGHT),
    PAC_DIRECTION_VERTICAL   = (PAC_DIRECTION_UP | PAC_DIRECTION_DOWN),

    PAC_DIRECTION_NEGATIVE = (PAC_DIRECTION_LEFT | PAC_DIRECTION_UP),
    PAC_DIRECTION_POSITIVE = (PAC_DIRECTION_RIGHT | PAC_DIRECTION_DOWN),
};

/**
 * @brief Small, unsigned integer type large enough to contain @ref pac_direction_e
 */
typedef unsigned char direction_t;

/**
 * @brief A little dude on the screen, either pac-man or a ghost.
 */
typedef struct actor_s
{
    // Entity:

    /**
     * @brief Pointer to concrete `pac_actor_update_`
     * @sa pac_actor_update_
     */
    void (*update)(struct actor_s *);

    /**
     * @brief Pointer to concrete `pac_actor_draw`
     * @sa pac_actor_draw
     */
    void (*draw)(const struct actor_s *);

    /// @private
    const atlas_t *_atlas;
    
    //

    /**
     * @brief The currently occupied tile
     * 
     * @todo refactor to be specified in units; necessary for spawning ghosts and starting level
     */
    tile_t current_tile[2];

    /**
     *  @brief How far along until the next tile.
     * 
     * This value is held in the range `0`, `PAC_UNITS_PER_TILE`.
     * @sa PAC_UNITS_PER_TILE
     */
    unit_t move_distance;

    /**
     * @brief Direction of movement.
     * 
     * The rightmost nibble stores the current direction of movement.
     * The leftmost nibble stores the next direction of movement.
     * For players, this is the bitmask of which directional inputs are currently depressed.
     * For ghosts, this is the direction the ghost will turn next tile.
     */
    direction_t flags;

    /// @privatesection
    unsigned char _palette;
    unsigned char _tile;
    unsigned char _flip_state;

    unsigned char _actor_flags;

    tile_t _target_tile[2];
}
actor_t;

/**
 * @brief Convert the given bitmask into a single enum value
 * 
 * @param flags direction(s) bitmask
 * @return The direction resulting from the rightmost set bit of @p flags
 */
direction_t pac_purify_direction(direction_t flags);

/**
 * @brief Check whether two direction flags are along the same axis.
 * 
 * @param a bitfield or single direction.
 * @param b bitfield or single direction.
 * @return a and b are both `PAC_DIRECTION_HORIZONTAL` or `PAC_DIRECTION_VERTICAL`
 */
int pac_same_axis(direction_t a, direction_t b);


/**
 * @brief Add @p amount to @p tile in-place, towards the direction @p flags.
 * 
 * @param[in,out] tile Value to add to
 * @param amount Amount to add
 * @param flags direction bitmask
 * 
 * @note This function implicity calls `pac_purify_direction`
 */
void pac_add_direction_to_tile(tile_t tile[2], tile_t amount, direction_t flags);

/**
 * @brief Add @p amount to @p unit in-place, towards the direction @p flags.
 * 
 * @param[in,out] unit Value to add to
 * @param amount Amount to add
 * @param flags direction bitmask
 * 
 * @note This function implicity calls `pac_purify_direction`
 */
void pac_add_direction_to_unit(unit_t unit[2], unit_t amount, direction_t flags);

unsigned int pac_get_opposite_direction(unsigned int direction);

/**
 * @brief Get the position of this actor.
 * @memberof actor_s
 * 
 * @param[out] position Current position in Unit Space
 */
void pac_actor_get_position(const actor_t *, unit_t position[2]);

/**
 * @memberof actor_s
 * @brief Draw this actor.
 * 
 * This is to be called once, in the main loop.
 */
void pac_actor_draw(const actor_t *);

void pac_actor_update();

/**
 * @pure @protected @memberof actor_s
 * @brief Update this actor.
 * 
 * This is to be called once before each draw(),
 * specifically by the main loop.
 */
void pac_actor_update_(actor_t *);

#endif