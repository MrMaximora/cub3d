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

void    take_texture_wall(t_game *game, int fd)
{
    char    *line;
    
    line = gnl(fd);
    while (game->map.n_textures < 6 && line != NULL)
    {
        if (line && ft_strlen(line) == 0)
        {
            free(line);
            line = gnl(fd);
            continue;
        }
        if (line && !ft_strncmp(line, "NO", 2))
            game->map.texture_wall_n = path_texture(game, line + 2);
        else if(line && !ft_strncmp(line, "SO", 2))
            game->map.texture_wall_s = path_texture(game, line + 2);
        else if(line && !ft_strncmp(line,"WE", 2))
            game->map.texture_wall_w = path_texture(game, line + 2);
        else if(line && !ft_strncmp(line,"EA", 2))
            game->map.texture_wall_e = path_texture(game, line + 2);
        else if (line && !ft_strncmp(line, "C", 1))
            game->map.cap_color = path_texture(game, line + 1);
        else if (line && !ft_strncmp(line, "F", 1))
            game->map.floor_color = path_texture(game, line + 1);
        free(line);
        line = gnl(fd);
    }
    if (game->map.n_textures != 6)
        exit_prog(game);
    if (line)
        free(line);
    printf("wall_n : %s\n", game->map.texture_wall_n);
    printf("wall_s : %s\n", game->map.texture_wall_s);
    printf("wall_e : %s\n", game->map.texture_wall_e);
    printf("wall_w : %s\n", game->map.texture_wall_w);
    printf("cap : %s\n", game->map.cap_color);
    printf("floor : %s\n", game->map.floor_color);
}

char    *path_texture(t_game *game, char *line)
{
    int     i;
    int     y;
    char    *path;

    i = 0;
    y = 0;
    while (is_white_space(line[y]))
        y++;
    path = malloc(ft_strlen(line) - y * sizeof(char) + 1);
    if (!path)
        exit_prog(game);
    while(line[y])
    {
        path[i] = line[y];
        i++;
        y++;
    }
    path[i] = '\0';
    game->map.n_textures += 1;
    return (path);
}