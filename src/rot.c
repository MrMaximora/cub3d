/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:50:40 by maxouvra          #+#    #+#             */
/*   Updated: 2025/01/14 12:50:43 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_right(t_game *game)
{
	float	old_dir_x;
	float	old_plane_x;

	old_plane_x = game->player.plane_x;
	old_dir_x = game->player.player_dir_x;
	game->player.player_dir_x = old_dir_x * cos(-game->player.rot_speed) \
		- game->player.player_dir_y * sin(-game->player.rot_speed);
	game->player.player_dir_y = old_dir_x * sin(-game->player.rot_speed) \
		+ game->player.player_dir_y * cos(-game->player.rot_speed);
	game->player.plane_x = old_plane_x * cos(-game->player.rot_speed) \
		- game->player.plane_y * sin(-game->player.rot_speed);
	game->player.plane_y = old_plane_x * sin(-game->player.rot_speed) \
		+ game->player.plane_y * cos(-game->player.rot_speed);
}

void	rotate_left(t_game *game)
{
	float	old_dir_x;
	float	old_plane_x;

	old_plane_x = game->player.plane_x;
	old_dir_x = game->player.player_dir_x;
	game->player.player_dir_x = old_dir_x * cos(game->player.rot_speed) \
		- game->player.player_dir_y * sin(game->player.rot_speed);
	game->player.player_dir_y = old_dir_x * sin(game->player.rot_speed) \
		+ game->player.player_dir_y * cos(game->player.rot_speed);
	game->player.plane_x = old_plane_x * cos(game->player.rot_speed) \
		- game->player.plane_y * sin(game->player.rot_speed);
	game->player.plane_y = old_plane_x * sin(game->player.rot_speed) \
		+ game->player.plane_y * cos(game->player.rot_speed);
}
