#ifndef JUMP_GAME_PLAYER
#define JUMP_GAME_PLAYER

#include "splashkit.h"

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum hero_type
{
    HERO0,
    HERO1,
    HERO2
};

/**
 * The player data keeps track of all of the information related to the player.
 *
 * @field   player_sprite   The players sprite
 * @field   dead            If the player is dead or not.
 * @field   kind            The movement of player to change by pressing A
 *
 **/
struct player_data
{
    sprite player_sprite;
    int x;
    int y;
    bool dead;
    hero_type kind;
};

player_data new_player();

/**
 * Handles the game control input
 *
 * @param player    The player to act on the input given
 **/
void handle_input(player_data &player);

/**
 * Switches the player type to the target and hides the others
 *
 * @param player    The player that is changing the types
 * @param target    The hero type you want to change too (steping forwards sprites in 3 parts, this one is idle)
 * @param hide1     The other hero type - step
 * @param hide2     The other hero type - step
 **/
void switch_player_sprites(player_data &player, hero_type target, hero_type hide1, hero_type hide2);

/**
 * Draws the player in the game
 *
 * @param player_to_draw    Draws the player to screen
 *
 **/
void draw_player(const player_data &player_to_draw);

/**
 * Updates the player in the game
 *
 * @param player_to_update   The player to update
 *
 **/
void update_player(player_data &player_to_update);

#endif