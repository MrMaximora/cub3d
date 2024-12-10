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

void    free_map(t_map *map) 
{
    unsigned int i;
    
    i = 0;
    while (i < map->height) 
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
}

void    print_map(t_map *map) 
{ 
    unsigned int i;
    
    i = 0;
    while (i < map->height)
    {
        printf("%s\n", map->grid[i]);
        i++;
    }
}

int main_loop(t_game *game)
{
    render_frame(game);
    return (0);
}

int main(int ac, char **av)
{
    t_game  game;

    if (ac != 2)
    {
        ft_error("Invalid number of arguments\n");
        return (1);
    }
    ft_parser_map(&game, av);
    print_map(&game.map);
    if (!validate_map(&game))
        printf("Map Invalid\n");
    init_game(&game);
    render_frame(&game);
    mlx_hook(&game.mlx.win_ptr, 2, 1L << 0, &handle_keys, &game);
    mlx_loop_hook(&game.mlx.mlx_ptr, &main_loop, &game);
    mlx_loop(&game.mlx.mlx_ptr);
    free_map(&game.map);
}