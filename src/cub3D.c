/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:25:00 by maxouvra          #+#    #+#             */
/*   Updated: 2024/11/14 10:25:02 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
		draw_wall(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, \
		game->map.image.img, 0, 0);
}

int	main_loop(t_game *game)
{
	render_frame(game);
	update_player_pos(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	game = (t_game){0};
	if (ac != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	init_game(&game);
	ft_parser_map(&game, av);
	if (!validate_map(&game))
	{
		printf("Map Invalid\n");
		exit_prog(&game);
	}
	game.mlx.win_ptr = mlx_new_window(game.mlx.mlx_ptr, \
		game.mlx.width_windows, game.mlx.height_windows, "cub3D");
	if (!game.mlx.mlx_ptr)
		exit(EXIT_FAILURE);
	load_textures(&game);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, handle_keys, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, handle_keys_release, &game);
	mlx_hook(game.mlx.win_ptr, 17, 1L << 17, exit_prog, &game);
	mlx_loop_hook(game.mlx.mlx_ptr, main_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
}
