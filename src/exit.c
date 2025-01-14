/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:30:33 by maxouvra          #+#    #+#             */
/*   Updated: 2025/01/08 15:55:49 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->grid)
		return ;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	exit_prog(t_game *game)
{
	free(game->map.path_texture_wall_n);
	free(game->map.path_texture_wall_s);
	free(game->map.path_texture_wall_e);
	free(game->map.path_texture_wall_w);
	if (game->map.image.img)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->map.image.img);
		mlx_destroy_image(game->mlx.mlx_ptr, game->map.texture_wall_e.img);
		mlx_destroy_image(game->mlx.mlx_ptr, game->map.texture_wall_n.img);
		mlx_destroy_image(game->mlx.mlx_ptr, game->map.texture_wall_s.img);
		mlx_destroy_image(game->mlx.mlx_ptr, game->map.texture_wall_w.img);
	}
	free_map(&game->map);
	if (game->mlx.mlx_ptr && game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_display(game->mlx.mlx_ptr);
	free(game->mlx.mlx_ptr);
	exit(EXIT_SUCCESS);
}
