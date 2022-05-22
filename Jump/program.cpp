#include "splashkit.h"

#define INITIAL_MOVE_SPEED_LEFT -4
#define MOVE_SPEED_LIMIT_LEFT -10
#define INITIAL_MOVE_SPEED_RIGHT 4
#define MOVE_SPEED_LIMIT_RIGHT 10

// Function to check the state of the players jump
void check_jump(sprite sprite)
{
    // Sets the jump height (in pixels)
    float jump_height = 90;
    // Sets the downward speed
    float jump_descend_speed = 4;
    // Checks if the sprite has gone above the jump height
    // If above jump height sets downward motion
    if (sprite_y(sprite) < sprite_value(sprite, "start_jump_y") - jump_height)
    {
        sprite_set_dy(sprite, jump_descend_speed);
    }
    // If the player has reached the bottom of the jump
    // Set y motion to 0
    // Place player on ground
    // Reset jumping value
    else if (sprite_y(sprite) > sprite_value(sprite, "start_jump_y") + 1)
    {
        sprite_set_dy(sprite, 0);
        sprite_set_y(sprite, sprite_value(sprite, "start_jump_y"));
        sprite_set_value(sprite, "jumping", 0);
    }
}

// Function to deal with player input
void player_input(sprite sprite)
{
    if (key_down(LEFT_KEY))
    {
        // If character is not already walking do this
        if (sprite_value(sprite, "walking") == 0)
        {
            // Set the animation. Identifier in hero_animation.txt
            sprite_start_animation(sprite, "WalkLeft");
            // Sets the character to walking
            sprite_set_value(sprite, "walking", 1);
            // Sets character forward motion
            sprite_set_dx(sprite, INITIAL_MOVE_SPEED_LEFT);
        }
        else
        {
            if (sprite_dx(sprite) > MOVE_SPEED_LIMIT_LEFT)
                sprite_set_dx(sprite, (sprite_dx(sprite) - 0.3));
        }

        // Sets sprite value "facing_left" to true
        sprite_set_value(sprite, "facing_left", 1);
    }
    if (key_down(RIGHT_KEY))
    {
        // If character is not already walking do this
        if (sprite_value(sprite, "walking") == 0)
        {
            // Set the animation. Identifier in hero_animation.txt
            sprite_start_animation(sprite, "WalkRight");
            // Sets the character to walking
            sprite_set_value(sprite, "walking", 1);
            // Sets character forward motion
            sprite_set_dx(sprite, INITIAL_MOVE_SPEED_RIGHT);
        }
        else
        {
            if (sprite_dx(sprite) < MOVE_SPEED_LIMIT_RIGHT)
                sprite_set_dx(sprite, (sprite_dx(sprite) + 0.4));
            // the number added after sprite handles the acceleration
        }

        // Sets sprite value "facing_left" to false
        sprite_set_value(sprite, "facing_left", 0);
    }
    if (key_typed(UP_KEY) && sprite_value(sprite, "jumping") == 0)
    {
        // Sets sprite "jumping" value to true
        sprite_set_value(sprite, "jumping", 1);
        // Sets the initial y value of the character to test for jump height
        sprite_set_value(sprite, "start_jump_y", sprite_y(sprite));
        // Sets the upward motion of the character
        sprite_set_dy(sprite, -4);
    }
    if ((key_released(RIGHT_KEY) || key_released(LEFT_KEY)))
    {
        // If left or right keys are released set character motion to zero
        sprite_set_dx(sprite, 0);
        // Set character walking to false
        sprite_set_value(sprite, "walking", 0);

        // Pick Idle animation based on which direction the sprite is facing
        if (sprite_value(sprite, "facing_left") == 0)
            sprite_start_animation(sprite, "IdleRight");
        else
            sprite_start_animation(sprite, "IdleLeft");
    }

    // If the player is jumping check the jump status
    if (sprite_value(sprite, "jumping") == 1)
        check_jump(sprite);
}

int main()
{
    // Load all the resources from bundle.txt in Resources/bundles
    load_resource_bundle("bundle", "bundle.txt");

    // Load the sprite. Uses the identifiers from bundle.txt
    sprite hero_sprite = create_sprite("Hero", "HeroAnim");

    // The sprite needs an initial position
    point_2d hero_position;
    // Setting the x value of the position
    hero_position.x = 20;
    // Setting the y value of the position
    hero_position.y = 700;

    // Set the initial position of the sprite
    sprite_set_position(hero_sprite, hero_position);
    // Scale the sprite if needed
    // sprite_set_scale(hero_sprite, 2.8);

    // Custom value added to sprite to check if sprite is walking: 0 = false, 1 = true
    sprite_add_value(hero_sprite, "walking", 0);
    // Custom value added to sprite to check if sprite is facing left: 0 = false, 1 = true
    sprite_add_value(hero_sprite, "facing_left", 0);

    sprite_add_value(hero_sprite, "jumping", 0);
    sprite_add_value(hero_sprite, "start_jump_y", 0);

    // Select the starting animation for the sprite
    // The animation identifiers are found in hero_animation.txt
    sprite_start_animation(hero_sprite, "IdleRight");

    // Open the game window
    open_window("Jump Platform Game", 1600, 900);
    // remove boarder with minimize, maximize and exit options *standard for all our aracade games*
    window_toggle_border("Jump Platform Game");

    while (!quit_requested())
    {
        // Draw Screen
        clear_screen(COLOR_BLUE);
        // Draws the background bitmap using the name from bundle.txt
        draw_bitmap("background", 0, -200);

        // draws the sprite to the screen
        draw_sprite(hero_sprite);

        // Checks if the player has entered any input
        player_input(hero_sprite);

        // If the sprite animation has ended it will replay the current animation
        if (sprite_animation_has_ended(hero_sprite))
            sprite_replay_animation(hero_sprite);

        // Updates the sprite each game loop
        update_sprite(hero_sprite);

        process_events();
        refresh_screen(60);

        // Breaks out of game loop. Frees memory and exits
        if (key_down(ESCAPE_KEY)) // this exits the game
            break;
    }

    // Free loaded bundle from memory before close
    free_resource_bundle("bundle");
    return 0;
}