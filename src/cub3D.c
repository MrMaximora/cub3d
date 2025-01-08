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

void	print_map(t_game *game)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < game->map.height)
	{
		while (x < ft_strlen(game->map.grid[y]))
		{
			putchar(game->map.grid[y][x]);
			x++;
		}
		putchar('\n');
		y++;
		x = 0;
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->map.texture_wall_n, game->map.path_texture_wall_n);
	load_texture(game, &game->map.texture_wall_s, game->map.path_texture_wall_s);
	load_texture(game, &game->map.texture_wall_e, game->map.path_texture_wall_e);
	load_texture(game, &game->map.texture_wall_w, game->map.path_texture_wall_w);
	game->map.image.data = (unsigned char *)mlx_get_data_addr(game->map.image.img, &game->map.image.bpp, &game->map.image.size_line, &game->map.image.endian);
	if (!game->map.image.data)
	{
		ft_error("Failed to get texture data address");
		exit_prog(game);
	}
}

void	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_error("Failed to load texture");
		exit_prog(game);
	}
	texture->data = (unsigned char *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
	if (!texture->data)
	{
		ft_error("Failed to get texture data address");
		exit_prog(game);
	}
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
		ft_error("Invalid number of arguments\n");
		return (1);
	}
	init_game(&game);
	ft_parser_map(&game, av);
	print_map(&game);
	if (!validate_map(&game))
		printf("Map Invalid\n");
	game.mlx.win_ptr = mlx_new_window(game.mlx.mlx_ptr, game.mlx.width_windows, game.mlx.height_windows, "cub3D");
	if (!game.mlx.mlx_ptr)
		exit(EXIT_FAILURE);
	load_textures(&game);
	render_frame(&game);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, handle_keys, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, handle_keys_release, &game);
	mlx_hook(game.mlx.win_ptr, 17, 1L << 17, exit_prog, &game);
	mlx_loop_hook(game.mlx.mlx_ptr, main_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
	free_map(&game.map);
}
