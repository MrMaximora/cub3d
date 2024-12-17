/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:30:42 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/10 16:30:44 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int handle_keys(int key, t_game *game)
{
    // Move the player forward (W key)
    if (key == XK_w)
    {
        game->player.player_x += game->player.ray_dir_x * game->player.move_speed;
        game->player.player_y += game->player.ray_dir_y * game->player.move_speed;
    }

    // Move the player backward (S key)
    if (key == XK_s)
    {
        game->player.player_x -= game->player.ray_dir_x * game->player.move_speed;
        game->player.player_y -= game->player.ray_dir_y * game->player.move_speed;
    }

    // Move the player left (A key) (strafe)
    if (key == XK_a)
    {
        game->player.player_x -= game->player.plane_x * game->player.move_speed;
        game->player.player_y -= game->player.plane_y * game->player.move_speed;
    }

    // Move the player right (D key) (strafe)
    if (key == XK_d)
    {
        game->player.player_x += game->player.plane_x * game->player.move_speed;
        game->player.player_y += game->player.plane_y * game->player.move_speed;
    }

    return 0;
}

int handle_key_release(int key, t_game *game)
{
    // Stop movement when the key is released
    if (key == XK_w || key == XK_s)
    {
        game->player.move_speed = 0; // Stop forward/backward movement
    }
    if (key == XK_a || key == XK_d)
    {
        game->player.move_speed = 0; // Stop strafing
    }
    return 0;
}