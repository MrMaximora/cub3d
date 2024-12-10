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
    if (key == XK_w)
        game->player.player_x += game->player.ray_dir_x * game->player.move_speed;
    if (key == XK_s)
        game->player.player_x -= game->player.ray_dir_x * game->player.move_speed;
    if (key == XK_a)
        game->player.player_y += game->player.ray_dir_y * game->player.move_speed;
    if (key == XK_d)
        game->player.player_y -= game->player.ray_dir_y * game->player.move_speed;

    return (0);
}