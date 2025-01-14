/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:37:07 by maxouvra          #+#    #+#             */
/*   Updated: 2025/01/14 12:37:09 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_closed(t_game *game, int new_y, int new_x)
{
	ft_solver_fill(game, new_y, new_x);
	if (ft_last_verif(game) == 0)
		return (1);
	return (0);
}

void	attribute(t_game *game, char c)
{
	float	length_plane;

	if (c == 'N')
	{
		game->player.player_dir_x = 0;
		game->player.player_dir_y = -1;
	}
	else if (c == 'S')
	{
		game->player.player_dir_x = 0;
		game->player.player_dir_y = 1;
	}
	else if (c == 'E')
	{
		game->player.player_dir_x = 1;
		game->player.player_dir_y = 0;
	}
	else if (c == 'W')
	{
		game->player.player_dir_x = -1;
		game->player.player_dir_y = 0;
	}
	length_plane = tan(66 / 2 * (M_PI / 180));
	game->player.plane_x = length_plane * -game->player.player_dir_y;
	game->player.plane_y = length_plane * game->player.player_dir_x;
}

int	place_player(t_game	*game, char c, int x, int y)
{
	int	player_count;

	player_count = 0;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player_count++;
		game->player.player_y = (float)y + 0.5;
		game->player.player_x = (float)x + 0.5;
		game->player.player_dir = c;
	}
	return (player_count);
}
