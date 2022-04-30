#ifndef JUMP_GAME_RESOURCES
#define JUMP_GAME_RESOURCES

#include "splashkit.h"
#include "player.h"

/**
 * The game data keeps track of all of the information related to the game.
 *
 * @field   game_over_sprite        The game over screen sprite
 * @field   player                  The player data struct
 * @field   platform_data               The platform data vector.
 * @field   kind                    Current platform_type kind
 * @field   game_started            Bool. Keeps track if the game has started or not.
 */
struct game_data
{
    sprite game_over_sprite;
    player_data player;
    // vector<platform_data> platform_data;
    // platform_type   kind;
    bool game_started;
};

/**
 * Creates a new game in the sets up the welcome and game over screen sprites.
 *
 * @returns     The new game data
 */
game_data new_game();

/**
 * Loads resource bundle
 */
void load_resources();

/**
 * Draws the game to the screen.
 *
 * @param player_to_draw   The player to draw to the screen
 * @param game             The game to draw to the screen
 */
void draw_game(const player_data &player_to_draw, game_data &game);

/**
 * Updates the game
 *
 * @param Game    The game to update
 */
void update_game(game_data &game);

#endif