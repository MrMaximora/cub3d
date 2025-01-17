/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:40:47 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/19 14:40:50 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	parse_line(t_game *game, char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args || args[0] == NULL || args[1] == NULL)
	{
		free_split(args);
		return ;
	}
	if (!ft_strncmp(args[0], "NO", 2) || !ft_strncmp(args[0], "SO", 2) || \
		!ft_strncmp(args[0], "WE", 2) || !ft_strncmp(args[0], "EA", 2))
		assign_texture(game, args[0], args[1]);
	else if (!ft_strncmp(args[0], "F", 1) || !ft_strncmp(args[0], "C", 1))
		assign_color(game, args[0], args[1]);
	else
	{
		free_split(args);
		printf("Invalid identifier in configuration file\n");
		exit_prog(game);
	}
	free_split(args);
}

void	assign_texture(t_game *game, char *identifier, char *path)
{
	if (ft_strnstr(path, ".xpm\n", ft_strlen(path)) == NULL)
	{
		printf("Invalid texture path format. Path must end with .xpm\n");
		exit_prog(game);
	}
	if (!ft_strncmp(identifier, "NO", 2))
		game->map.path_texture_wall_n = ft_strndup(path, ft_strlen(path) - 1);
	else if (!ft_strncmp(identifier, "SO", 2))
		game->map.path_texture_wall_s = ft_strndup(path, ft_strlen(path) - 1);
	else if (!ft_strncmp(identifier, "WE", 2))
		game->map.path_texture_wall_w = ft_strndup(path, ft_strlen(path) - 1);
	else if (!ft_strncmp(identifier, "EA", 2))
		game->map.path_texture_wall_e = ft_strndup(path, ft_strlen(path) - 1);
	else
	{
		printf("Unknown texture identifier\n");
		exit_prog(game);
	}
	game->map.n_textures++;
}

void	assign_color_help(t_game *game, char *identifier, char **rgb)
{
	if (!ft_strncmp(identifier, "F", 1))
		game->map.floor_color = (game->map.r << 16) | (game->map.g << 8) \
			| game->map.b;
	else if (!ft_strncmp(identifier, "C", 1))
		game->map.cap_color = (game->map.r << 16) | (game->map.g << 8) | \
			game->map.b;
	else
	{
		free_split(rgb);
		printf("Unknown color identifier\n");
		exit_prog(game);
	}
}

void	assign_color(t_game *game, char *identifier, char *value)
{
	char	**rgb;

	rgb = ft_split(value, ',');
	if (!rgb || ft_split_len(rgb) != 3)
	{
		printf("Invalid color format\n");
		exit_prog(game);
	}
	game->map.r = ft_atoi(rgb[0]);
	game->map.g = ft_atoi(rgb[1]);
	game->map.b = ft_atoi(rgb[2]);
	if (game->map.r < 0 || game->map.r > 255 || game->map.g < 0 || \
		game->map.g > 255 || game->map.b < 0 || game->map.b > 255)
	{
		free_split(rgb);
		printf("Color values must be between 0 and 255\n");
		exit_prog(game);
	}
	assign_color_help(game, identifier, rgb);
	free_split(rgb);
	game->map.n_colors++;
}

void	parse_config(t_game *game, int fd)
{
	char	*line;

	line = gnl(fd);
	while (line)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		parse_line(game, line);
		free(line);
		if (game->map.n_textures == 4 && game->map.n_colors == 2)
			break ;
		line = gnl(fd);
	}
	if (game->map.n_textures != 4 || game->map.n_colors != 2)
	{
		printf("Incomplete configuration: Missing textures or colors\n");
		exit_prog(game);
	}
}
