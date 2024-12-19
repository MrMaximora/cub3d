/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:48:10 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/19 12:48:11 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void    move_forward(t_game *game)
{
    if (game->map.grid[(int)(game->player.player_y)][(int)(game->player.player_x + game->player.player_dir_x * game->player.move_speed)] != '1')
        game->player.player_x += game->player.player_dir_x * game->player.move_speed;
    if (game->map.grid[(int)(game->player.player_y + game->player.player_dir_y * game->player.move_speed)][(int)(game->player.player_x)] != '1')
        game->player.player_y += game->player.player_dir_y * game->player.move_speed;
}

void    move_backward(t_game *game)
{
    if (game->map.grid[(int)(game->player.player_y)][(int)(game->player.player_x - game->player.player_dir_x * game->player.move_speed)] != '1')
        game->player.player_x -= game->player.player_dir_x * game->player.move_speed;
    if (game->map.grid[(int)(game->player.player_y - game->player.player_dir_y * game->player.move_speed)][(int)(game->player.player_x)] != '1')
        game->player.player_y -= game->player.player_dir_y * game->player.move_speed;
}

void strafe_right(t_game *game)
{
    if (game->map.grid[(int)(game->player.player_y)][(int)(game->player.player_x - game->player.player_dir_y * game->player.move_speed)] != '1')
        game->player.player_x -= game->player.player_dir_y * game->player.move_speed;
    if (game->map.grid[(int)(game->player.player_y + game->player.player_dir_x * game->player.move_speed)][(int)(game->player.player_x)] != '1')
        game->player.player_y += game->player.player_dir_x * game->player.move_speed;
}


void    strafe_left(t_game *game)
{
    if (game->map.grid[(int)(game->player.player_y)][(int)(game->player.player_x + game->player.player_dir_y * game->player.move_speed)] != '1')
        game->player.player_x += game->player.player_dir_y * game->player.move_speed;
    if (game->map.grid[(int)(game->player.player_y - game->player.player_dir_x * game->player.move_speed)][(int)(game->player.player_x)] != '1')
        game->player.player_y -= game->player.player_dir_x * game->player.move_speed;
}

void    rotate_right(t_game *game)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = game->player.player_dir_x;
    game->player.player_dir_x = game->player.player_dir_x * cos(-game->player.rot_speed) - game->player.player_dir_y * sin(-game->player.rot_speed);
    game->player.player_dir_y = old_dir_x * sin(-game->player.rot_speed) + game->player.player_dir_y * cos(-game->player.rot_speed);
    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(-game->player.move_speed) - game->player.plane_y * sin(-game->player.rot_speed);
    game->player.plane_y = old_plane_x * sin(-game->player.rot_speed) + game->player.plane_y * cos(-game->player.rot_speed); 
}

void    rotate_left(t_game *game)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = game->player.player_dir_x;
    game->player.player_dir_x = game->player.player_dir_x * cos(game->player.rot_speed) - game->player.player_dir_y * sin(game->player.rot_speed);
    game->player.player_dir_y = old_dir_x * sin(game->player.rot_speed) + game->player.player_dir_y * cos(game->player.rot_speed);
    old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(game->player.move_speed) - game->player.plane_y * sin(game->player.rot_speed);
    game->player.plane_y = old_plane_x * sin(game->player.rot_speed) + game->player.plane_y * cos(game->player.rot_speed);
}
