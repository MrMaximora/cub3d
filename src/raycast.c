/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:01:08 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/10 16:01:09 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	calculate_ray(t_game *game, int x)
{
	game->player.camera_x = 2 * x / (float)game->mlx.width_windows - 1.0;
	game->player.ray_dir_x = game->player.player_dir_x + game->player.plane_x * game->player.camera_x;
	game->player.ray_dir_y = game->player.player_dir_y + game->player.plane_y * game->player.camera_x;
	game->map.map_x = (int)game->player.player_x;
	game->map.map_y = (int)game->player.player_y;
	game->map.delta_dist_x = fabs(1 / game->player.ray_dir_x);
	game->map.delta_dist_y = fabs(1 / game->player.ray_dir_y);
	calculate_step_and_side_dist(game);
}

void	calculate_step_and_side_dist(t_game *game)
{
	if (game->player.ray_dir_x < 0)
	{
		game->player.step_x = -1;
		game->map.side_dist_x = (game->player.player_x - game->map.map_x) * game->map.delta_dist_x;
	}
	else
	{
		game->player.step_x = 1;
		game->map.side_dist_x = (game->map.map_x + 1.0 - game->player.player_x) * game->map.delta_dist_x;
	}
	if (game->player.ray_dir_y < 0)
	{
		game->player.step_y = -1;
		game->map.side_dist_y = (game->player.player_y - game->map.map_y) * game->map.delta_dist_y;
	}
	else
	{
		game->player.step_y = 1;
		game->map.side_dist_y = (game->map.map_y + 1.0 - game->player.player_y) * game->map.delta_dist_y;
	}
}

void	perform_dda(t_game *game)
{
	while (game->map.hit_wall == 0)
	{
		if (game->map.side_dist_x < game->map.side_dist_y)
		{
			game->map.side_dist_x += game->map.delta_dist_x;
			game->map.map_x += game->player.step_x;
			game->map.side = 0;
		}
		else
		{
			game->map.side_dist_y += game->map.delta_dist_y;
			game->map.map_y += game->player.step_y;
			game->map.side = 1;
		}
		if (game->map.grid[game->map.map_y][game->map.map_x] == '1')
			game->map.hit_wall = 1;
	}
	calculate_dist(game);
}

void	calculate_dist(t_game *game)
{
	if (game->map.side == 0)
		game->map.perp_wall_dist = (game->map.map_x - game->player.player_x + (1 - game->player.step_x) / 2) / game->player.ray_dir_x;
	else
		game->map.perp_wall_dist = (game->map.map_y - game->player.player_y + (1 - game->player.step_y) / 2) / game->player.ray_dir_y;
	if (game->map.perp_wall_dist < 0)
		game->map.perp_wall_dist = fabs(game->map.perp_wall_dist);
}

void	calculate_wall_height(t_game *game)
{
	game->map.line_height = (int)(game->mlx.height_windows / game->map.perp_wall_dist);
	game->map.draw_start = (-game->map.line_height / 2) + (game->mlx.height_windows / 2);
	game->map.draw_end = (game->map.line_height / 2) + (game->mlx.height_windows / 2);
}

void	calculate_for_texture(t_game *game, t_texture *actual_wall)
{
	if (game->map.side == 0)
		game->map.wall_x = game->player.player_y + game->map.perp_wall_dist * game->player.ray_dir_y;
	else
		game->map.wall_x = game->player.player_x + game->map.perp_wall_dist * game->player.ray_dir_x;
	game->map.wall_x -= floor(game->map.wall_x);
	if (game->map.wall_x < 0)
		game->map.wall_x = 0;
	if (game->map.wall_x > 1)
		game->map.wall_x = 1;
	game->map.tex_x = (int)(game->map.wall_x * (float)actual_wall->width);
	if ((game->map.side == 0 && game->player.ray_dir_x > 0) || (game->map.side == 1 && game->player.ray_dir_y < 0))
		game->map.tex_x = actual_wall->width - game->map.tex_x - 1;
	game->map.step = (float)(actual_wall->height - 1) / (float)(game->map.draw_end - game->map.draw_start - 1);
	game->map.texture_bpp = actual_wall->bpp / 8;
	game->map.constant_column = game->map.tex_x * game->map.texture_bpp;
	game->map.total_texture_size = actual_wall->width * actual_wall->height * game->map.texture_bpp;
}

void	render_frame(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->mlx.width_windows)
	{
		game->map.hit_wall = 0;
		calculate_ray(game, x);
		perform_dda(game);
		calculate_wall_height(game);
		draw_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->map.image.img, 0, 0);
}

void	my_mlx_pixel_put(t_texture *texture, int x, int y, int color)
{
	unsigned char	*dst;

	dst = texture->data + (y * texture->size_line + x * 4);
	*(unsigned int *)dst = color;
}

void	draw_column(t_game *game, int x)
{
	t_texture	wall_texture;
	int			y;
	int			color;
	int			index;

	if (game->map.side == 0 && game->player.step_x > 0)
		wall_texture = game->map.texture_wall_n;
	else if (game->map.side == 0 && game->player.step_x < 0)
		wall_texture = game->map.texture_wall_s;
	else if (game->map.side == 1 && game->player.step_y > 0)
		wall_texture = game->map.texture_wall_e;
	else if (game->map.side == 1 && game->player.step_y < 0)
		wall_texture = game->map.texture_wall_w;
	calculate_for_texture(game, &wall_texture);
	y = game->map.draw_start - 1;
	if (y < 0)
		y = 0;
	while (y < game->map.draw_end)
	{
		game->map.tex_y = (float)(y - game->map.draw_start - 1) * game->map.step;
		index = game->map.tex_y * wall_texture.width * game->map.texture_bpp + game->map.constant_column;
		if (index >= 0 && index < game->map.total_texture_size)
		{
			color = (wall_texture.data[index + 2] << 16) | (wall_texture.data[index + 1] << 8)  | (wall_texture.data[index]);
			if (y >= 0 && y < game->mlx.height_windows)
				my_mlx_pixel_put(&game->map.image, x, y, color);
		}
		y++;
		if (y > game->mlx.height_windows)
			break ;
	}
	y = 0;
	while (y <= game->map.draw_start)
	{
		if (y >= 0 && y < game->mlx.height_windows)
			my_mlx_pixel_put(&game->map.image, x, y, game->map.cap_color);
		y++;
	}
	y = game->map.draw_end - 1;
	while (y < game->mlx.height_windows)
	{
		if (y >= 0 && y < game->mlx.height_windows)
			my_mlx_pixel_put(&game->map.image, x, y, game->map.floor_color);
		y++;
	}
}
