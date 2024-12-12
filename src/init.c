/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:42:41 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/10 15:42:42 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void init_game(t_game *game)
{
    t_player    player;

    player = game->player;
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
        exit(EXIT_FAILURE);
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, 800, 600, "cub3D");
    if (!game->mlx.mlx_ptr)
        exit(EXIT_FAILURE);
    game->player.player_x = 0.0;
    game->player.player_y = 0.0;
    game->player.plane_x = 0.0;
    game->player.plane_y = 0.66;
    game->player.ray_dir_x = 0.0;
    game->map.delta_dist_x = 0.0;
    game->player.ray_dir_y = 0.0;
    game->map.delta_dist_y = 0.0;
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    game->player.camera_x = 0.0;
    game->map.hit_wall = 0;
    game->map.side = 0;
    game->map.top = 0;
    game->map.stack_size = 0;
}