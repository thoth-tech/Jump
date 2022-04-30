#include "splashkit.h"
#include "game.h"
#include "player.h"

/**
 * The hero bitmap function converts a hero kind into a
 * bitmap that can be used.
 *
 * Not exposed by the header.
 *
 * @param kind  The kind of hero you want the bitmap of
 * @return      The bitmap matching this hero kind
 */

// bool key_released(key_code key);

bitmap hero_bitmap(hero_type type)
{
    switch (type)
    {
    case HERO0:
        return bitmap_named("hero0");
    case HERO1:
        return bitmap_named("hero1");
    case HERO2:
        return bitmap_named("hero2");
    default:
        return bitmap_named("hero1");
    }
}

player_data new_player()
{
    player_data result;

    bitmap player_bitmap = hero_bitmap(HERO1);

    result.player_sprite = create_sprite(player_bitmap);

    sprite_add_layer(result.player_sprite, hero_bitmap(HERO2), "hero0");
    sprite_add_layer(result.player_sprite, hero_bitmap(HERO0), "hero2");

    sprite_hide_layer(result.player_sprite, "hero0");
    sprite_hide_layer(result.player_sprite, "hero2");

    sprite_set_x(result.player_sprite, screen_width() / 2);
    sprite_set_y(result.player_sprite, screen_height() / 2);
    result.x = sprite_x(result.player_sprite);

    return result;
}

void switch_player_sprites(player_data &player, hero_type target, hero_type hide1, hero_type hide2)
{
    if (player.kind != target)
    {
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(hide1));
        sprite_hide_layer(player.player_sprite, static_cast<int>(hide2));
    }
}

void handle_input(player_data &player)
{
    if (player.dead == false)
    {
        if (key_down(RIGHT_KEY))
        {
            switch_player_sprites(player, HERO2, HERO0, HERO1);
            sprite_set_x(player.player_sprite, player.x += 10); // 10 = speed
        }

        if (key_down(LEFT_KEY))
        {
            switch_player_sprites(player, HERO1, HERO0, HERO2); // will create left moving image or flip
            sprite_set_x(player.player_sprite, player.x -= 10); // 10 = speed
        }

        if (key_down(D_KEY)) // this moves the arm position forward will be attack_key in future
        {
            switch_player_sprites(player, HERO1, HERO0, HERO2);
        }

        // if (key_released(RIGHT_KEY) or key_released(LEFT_KEY))
        // {
        //     switch_player_sprites(player, HERO0, HERO2, HERO1);
        // } // trying to return the hero to idle when not moving

        // jump if (key_pressed(A_KEY))
    }
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    update_sprite(player_to_update.player_sprite);

    switch_player_sprites(player_to_update, HERO0, HERO1, HERO2);
}