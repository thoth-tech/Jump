#include "splashkit.h"
#include "player.h"
#include "game.h"

using namespace std;

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "jump_game_resources.txt");
}

game_data new_game()
{
    game_data game;

    game.player = new_player();

    // if (game.game_started == false)
    // {
    //     // draw player sprite to center screen
    //     sprite_set_y(game.player.player_sprite, (screen_height() / 2) - 37);
    //     sprite_set_x(game.player.player_sprite, (screen_width() / 2) - 19);
    // }
    // else
    // {
    //     sprite_hide_layer(game.game_over_sprite, 0);
    // }

    game.game_started = false;

    game.player.dead = false;

    return game;
}

void draw_game_over_screen(game_data &game)
{
    if (game.game_started == false)
    {
        draw_sprite(game.game_over_sprite, 50, 150);
    }
}

void game_over(game_data &game)
{
    game.player.dead = true;
    game.game_started = false;
}

void game_over_next(game_data &game)
{
    game.player.dead = false;
    game.game_started = false;
}

void draw_background(game_data &game)
{
    draw_bitmap("background", 0, 0, option_to_screen());

    // draw_bitmap("base", 0, 400, option_to_screen());

    if (game.player.dead == true and game.game_started == false)
    {
        draw_game_over_screen(game);
    }
}

void update_game(game_data &game)
{
    update_player(game.player);

    // need to add in platform data here

    if (key_typed(SPACE_KEY) or key_typed(D_KEY))
    {
        if (game.player.dead == false and game.game_started == false)
        {
            game.game_started = true;
        }
    }

    if (game.player.dead == true and game.game_started == false)
    {
        // should this be changed for esc exit as well?
        while (key_typed(SPACE_KEY) or key_typed(D_KEY))
        {
            process_events();
            game_over_next(game);
        }
    }
}

void draw_game(const player_data &player_to_draw, game_data &game)
{
    clear_screen(COLOR_BLACK);

    draw_background(game);

    draw_player(player_to_draw);

    refresh_screen(60);
}