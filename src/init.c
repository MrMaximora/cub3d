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

void	init_help(t_game *game)
{
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

void	init_game(t_game *game)
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
	game->map.n_colors = 0;
	game->map.n_textures = 0;
	game->player.player_x = 0.0;
	game->player.player_y = 0.0;
	game->player.ray_dir_x = 0.0;
	game->map.delta_dist_x = 0.0;
	game->player.ray_dir_y = 0.0;
	game->player.player_dir_x = 0.0;
	init_help(game);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->map.texture_wall_n, \
		game->map.path_texture_wall_n);
	load_texture(game, &game->map.texture_wall_s, \
		game->map.path_texture_wall_s);
	load_texture(game, &game->map.texture_wall_e, \
		game->map.path_texture_wall_e);
	load_texture(game, &game->map.texture_wall_w, \
		game->map.path_texture_wall_w);
	game->map.image.data = \
		(unsigned char *)mlx_get_data_addr(game->map.image.img, \
			&game->map.image.bpp, &game->map.image.size_line, \
				&game->map.image.endian);
	if (!game->map.image.data)
	{
		printf("Failed to get texture data address\n");
		exit_prog(game);
	}
}

void	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, \
		&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Failed to load texture\n");
		exit_prog(game);
	}
	texture->data = (unsigned char *)mlx_get_data_addr(texture->img, \
		&texture->bpp, &texture->size_line, &texture->endian);
	if (!texture->data)
	{
		printf("Failed to get texture data address\n");
		exit_prog(game);
	}
}
