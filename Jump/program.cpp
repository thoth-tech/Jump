#include "splashkit.h"
#include <iostream>
#include "game.h"
using namespace std;

int main()
{
    open_window("Jump Platform Game", 1600, 900);
    // window_toggle_border(); *need help here.
    load_resources();
    clear_screen(COLOR_BLUE);

    game_data game = new_game();

    while (not quit_requested())
    {
        process_events();
        handle_input(game.player);
        draw_game(game.player, game);
        update_game(game);

        if (key_down(ESCAPE_KEY)) // this exits the game
        {
            return 0;
        }
    }

    // refresh_screen();
    // delay(5000);
    return 0;
}