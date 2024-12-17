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

void ft_solver_fill(t_game *game, int start_y, int start_x)
{
    t_point *stack;
    t_point current;

    printf("pos[%d][%d]\n",start_y, start_x);
    game->map.stack_size = game->map.height * game->map.width;
    game->map.top = 0;
    stack = malloc(game->map.stack_size * sizeof(t_point));
    if (!stack)
        return;
    stack[game->map.top++] = (t_point){start_y, start_x};

    while (game->map.top > 0)
    {
        current = stack[--game->map.top];
        // Skip if already filled or invalid position (boundary or walls)
        if (game->map.grid[current.y][current.x] == 'V' ||
            game->map.grid[current.y][current.x] == '1' || 
            game->map.grid[current.y][current.x] == ' ' || 
            current.y == 0 || current.y == game->map.height - 1 ||
            current.x == 0 || current.x == game->map.width - 1)
            continue;
        // Mark the current position as 'V' (visited)
        game->map.grid[current.y][current.x] = 'V';
        // Check adjacent positions
        if (current.y > 0 && game->map.grid[current.y - 1][current.x] == '0')
            stack[game->map.top++] = (t_point){current.y - 1, current.x};
        if (current.y + 1 < game->map.height && game->map.grid[current.y + 1][current.x] == '0')
            stack[game->map.top++] = (t_point){current.y + 1, current.x};
        if (current.x > 0 && game->map.grid[current.y][current.x - 1] == '0')
            stack[game->map.top++] = (t_point){current.y, current.x - 1};
        if (current.x + 1 < game->map.width && game->map.grid[current.y][current.x + 1] == '0')
            stack[game->map.top++] = (t_point){current.y, current.x + 1};

        // Ensure that the stack does not overflow
        if (game->map.top >= game->map.stack_size)
        {
            free(stack);
            return;
        }
    }
    // After filling the grid with 'V', print the map
    print_map(game);
    free(stack);
}

int ft_last_verif(t_game *game)
{
    int    x;
    int    y;
    char            current;

    y = 0;
    while (y < game->map.height)    
    {
        x = 0;
        while (x < game->map.width)
        {
            current = game->map.grid[y][x];
            if (current == '0' || current == 'V' || current == 'N')
            {
                if (x == 0 || y == 0 || y == game->map.height - 1 || x == game->map.width - 1)
                {
                    if (current != '1')
                        return 1;
                }
                if (y > 0 && (game->map.grid[y - 1][x] == ' ' || game->map.grid[y - 1][x] == '\0'))
                    return 1;
                if (y + 1 < game->map.height && (game->map.grid[y + 1][x] == ' ' || game->map.grid[y + 1][x] == '\0'))
                    return 1;
                if (x > 0 && (game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x - 1] == '\0'))
                    return 1;
                if (x + 1 < game->map.width && (game->map.grid[y][x + 1] == ' ' || game->map.grid[y][x + 1] == '\0'))
                    return 1;
            }
            x++;
        }
        y++;
    }
    return 0;
}

