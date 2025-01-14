/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:53:19 by maxouvra          #+#    #+#             */
/*   Updated: 2025/01/14 12:53:23 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	calculate_for_texture(t_game *game, t_texture *actual_wall)
{
	if (game->map.side == 0)
		game->map.wall_x = game->player.player_y + game->map.perp_wall_dist \
			* game->player.ray_dir_y;
	else
		game->map.wall_x = game->player.player_x + game->map.perp_wall_dist \
			* game->player.ray_dir_x;
	game->map.wall_x -= floor(game->map.wall_x);
	if (game->map.wall_x < 0)
		game->map.wall_x = 0;
	if (game->map.wall_x > 1)
		game->map.wall_x = 1;
	game->map.tex_x = (int)(game->map.wall_x * (float)actual_wall->width);
	if ((game->map.side == 0 && game->player.ray_dir_x > 0) || \
		(game->map.side == 1 && game->player.ray_dir_y < 0))
		game->map.tex_x = actual_wall->width - game->map.tex_x - 1;
	game->map.step = (float)(actual_wall->height - 1) \
		/ (float)(game->map.draw_end - game->map.draw_start - 1);
	game->map.bpp = actual_wall->bpp / 8;
	game->map.constant_column = game->map.tex_x * game->map.bpp;
	game->map.total_texture_size = actual_wall->width * actual_wall->height \
		* game->map.bpp;
}

void	my_mlx_pixel_put(t_texture *texture, int x, int y, int color)
{
	unsigned char	*dst;

	dst = texture->data + (y * texture->size_line + x * 4);
	*(unsigned int *)dst = color;
}

t_texture	*wall_dir(t_texture *wall_dir, t_game *game)
{
	if (game->map.side == 0 && game->player.step_x > 0)
		wall_dir = &game->map.texture_wall_n;
	else if (game->map.side == 0 && game->player.step_x < 0)
		wall_dir = &game->map.texture_wall_s;
	else if (game->map.side == 1 && game->player.step_y > 0)
		wall_dir = &game->map.texture_wall_e;
	else if (game->map.side == 1 && game->player.step_y < 0)
		wall_dir = &game->map.texture_wall_w;
	return (wall_dir);
}

void	draw_cap_floor(t_game *game, int x)
{
	int	y;

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

void	draw_wall(t_game *game, int x)
{
	t_texture	wall;
	int			y;

	wall = *wall_dir(&wall, game);
	calculate_for_texture(game, &wall);
	y = game->map.draw_start - 1;
	if (y < 0)
		y = 0;
	while (y++ < game->map.draw_end)
	{
		game->map.tex_y = (float)(y - game->map.draw_start - 1) \
			* game->map.step;
		game->map.px = game->map.tex_y * wall.width * game->map.bpp \
			+ game->map.constant_column;
		if (game->map.px >= 0 && game->map.px < game->map.total_texture_size)
		{
			game->map.color = (wall.data[game->map.px + 2] << 16) | \
				(wall.data[game->map.px + 1] << 8) | (wall.data[game->map.px]);
			if (y >= 0 && y < game->mlx.height_windows)
				my_mlx_pixel_put(&game->map.image, x, y, game->map.color);
		}
		if (y > game->mlx.height_windows)
			break ;
	}
	draw_cap_floor(game, x);
}
