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
    game->mlx.height_windows = 720;
    game->mlx.width_windows = 1280;
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
        exit(EXIT_FAILURE);
    game->map.path_texture_wall_n = NULL;
    game->map.path_texture_wall_e = NULL;
    game->map.path_texture_wall_s = NULL;
    game->map.path_texture_wall_w = NULL;
    game->map.image.img = mlx_new_image(game->mlx.mlx_ptr, 1280, 720);
    game->map.floor_color = 0;
    game->map.cap_color = 0;
    game->map.n_colors  = 0;
    game->map.n_textures = 0;
    game->player.player_x = 0.0;
    game->player.player_y = 0.0;
    game->player.ray_dir_x = 0.0;
    game->map.delta_dist_x = 0.0;
    game->player.ray_dir_y = 0.0;
    game->player.player_dir_x = 0.0;
    game->player.player_dir_y = 0.0;
    game->map.delta_dist_y = 0.0;
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    game->player.camera_x = 0.0;
    game->map.hit_wall = 0;
    game->map.side = 0;
    game->map.top = 0;
    game->map.stack_size = 0;
    game->player.move_backward = 0;
    game->player.move_forward = 0;
    game->player.strafe_left = 0;
    game->player.strafe_right = 0;
    game->player.rotate_left = 0;
    game->player.rotate_right = 0;
    game->map.n_textures = 0;
    game->map.grid = NULL;
    game->map.height = 0;
    game->map.width = 0;
}