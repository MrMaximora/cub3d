/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:47:35 by maxouvra          #+#    #+#             */
/*   Updated: 2024/11/14 10:47:38 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	int		map_started;

	parse_config(game, fd);
	line = gnl(fd);
	map_started = 0;
	while (line != NULL)
	{
		if (!map_started && ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map_started = 1;
		game->map.grid = ft_realloc(game->map.grid, sizeof(char *)* (game->map.height + 1));
		game->map.grid[game->map.height] = line;
		game->map.height++;
		if (ft_strlen(line) > game->map.width)
			game->map.width = ft_strlen(line);
		line = gnl(fd);
	}
	if (game->map.grid)
		game->map.grid[game->map.height] = NULL;
}

void	ft_parser_map(t_game *game, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("fd invalid or not found\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(av[1], ".cub", ft_strlen(av[1])) == NULL)
	{
		close(fd);
		printf("fd not finish by .cub\n");
		exit(EXIT_FAILURE);
	}
	ft_read_map(game, fd);
	close(fd);
}

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

int	verif_player_and_map(t_game *game, int player_count)
{
	if (player_count != 1)
	{
		printf("Error: Invalid number of players (found %d)\n", player_count);
		return (0);
	}
	if (!is_closed(game, game->player.player_y, game->player.player_x))
	{
		printf("Error: Map is not closed!\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int		x;
	int		y;
	int		player_count;
	char	c;

	y = 0;
	player_count = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (!is_valid_char(c))
			{
				printf("Error: Invalid character '%c' at (%d, %d)\n", c, y, x);
				return (0);
			}
			player_count += place_player(game, c, y, x);
			attribute(game, c);
			x++;
		}
		y++;
	}
	return (verif_player_and_map(game, player_count));
}
