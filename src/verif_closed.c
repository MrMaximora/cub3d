/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif-closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:09:34 by maxouvra          #+#    #+#             */
/*   Updated: 2024/11/20 10:09:36 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ft_solver_fill(t_game *game, unsigned int start_x, unsigned int start_y)
{
    t_point *stack;
    t_point current;

    game->map.stack_size = game->map.height * game->map.width;
    game->map.top = 0;
    stack = malloc(game->map.stack_size * sizeof(t_point));
    if (!stack)
        return;
    stack[game->map.top++] = (t_point){start_x, start_y};
    while (game->map.top > 0)
    {
        current = stack[--game->map.top];
        if (game->map.grid[current.x][current.y] == 'V' ||
            game->map.grid[current.x][current.y] == '1' || 
            game->map.grid[current.x][current.y] == ' ' || 
			current.x == 0 || current.x == game->map.height - 1 ||
            current.y == 0 || current.y == game->map.width - 1)
            continue;
        game->map.grid[current.x][current.y] = 'V';
        if (current.x > 0 && game->map.grid[current.x - 1][current.y] == '0')
            stack[game->map.top++] = (t_point){current.x - 1, current.y};
        if (current.x + 1 < game->map.height && game->map.grid[current.x + 1][current.y] == '0')
            stack[game->map.top++] = (t_point){current.x + 1, current.y};
        if (current.y > 0 && game->map.grid[current.x][current.y - 1] == '0')
            stack[game->map.top++] = (t_point){current.x, current.y - 1};
        if (current.y + 1 < game->map.width && game->map.grid[current.x][current.y + 1] == '0')
            stack[game->map.top++] = (t_point){current.x, current.y + 1};
        if (game->map.top >= game->map.stack_size)
        {
            free(stack);
            return;
        }
    }
    print_map(game);
    free(stack);
}

int ft_last_verif(t_game *game)
{
    unsigned int    x;
    unsigned int    y;
    char            current;

    x = 0;
    while (x < game->map.height)    
    {
        y = 0;
        while (y < ft_strlen(game->map.grid[x]))
        {
            current = game->map.grid[x][y];
            if (current == '0' || current == 'V' || current == 'N')
            {
                if (x == 0 || y == 0 || x == game->map.height - 1 || y == game->map.width - 1)
                {
                    if (current != '1')
                        return 1;
                }
                if (x > 0 && (game->map.grid[x - 1][y] == ' ' || game->map.grid[x - 1][y] == '\0'))
                    return 1;
                if (x + 1 < game->map.height && (game->map.grid[x + 1][y] == ' ' || game->map.grid[x + 1][y] == '\0'))
                    return 1;
                if (y > 0 && (game->map.grid[x][y - 1] == ' ' || game->map.grid[x][y - 1] == '\0'))
                    return 1;
                if (y + 1 < game->map.width && (game->map.grid[x][y + 1] == ' ' || game->map.grid[x][y + 1] == '\0'))
                    return 1;
            }
            y++;
        }
        x++;
    }
    return 0;
}

