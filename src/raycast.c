/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:01:08 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/10 16:01:09 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void raycasting(t_game *game)
{
    unsigned int x;
    
    x = 0;
    game->map.width = 800;
    game->map.height = 600;

    while (x < game->map.width)
    {
        calculate_ray(game, x);
        perform_dda(game);
        draw_column(game, x);
        x++;
    }
}

void calculate_ray(t_game *game, int x)
{
    game->player.camera_x = 2 * x / (double)game->map.width - 1;
    game->player.ray_dir_x = game->player.player_dir + game->player.plane_x * game->player.camera_x;
    game->player.ray_dir_y = game->player.player_dir + game->player.plane_y * game->player.camera_x;
    game->map.stack_size = (int)game->player.player_x;
    game->map.stack_size = (int)game->player.player_y;
    if (game->player.ray_dir_x == 0)
        game->map.delta_dist_x = 1e30;
    else
        game->map.delta_dist_x = fabs(1 / game->player.ray_dir_x);

    if (game->player.ray_dir_y == 0)
        game->map.delta_dist_y = 1e30;
    else
        game->map.delta_dist_y = fabs(1 / game->player.ray_dir_y);
}

void perform_dda(t_game *game)
{
    if (game->player.ray_dir_x < 0)
    {
        game->player.step_x = -1;
        game->map.delta_dist_x = (game->player.player_x - game->map.stack_size) * game->map.delta_dist_x;
    }
    else
    {
        game->player.step_x = 1;
        game->map.delta_dist_x = (game->map.stack_size + 1.0 - game->player.player_x) * game->map.delta_dist_x;
    }
    if (game->player.ray_dir_y < 0)
    {
        game->player.step_y = -1;
        game->map.delta_dist_y = (game->player.player_y - game->map.stack_size) * game->map.delta_dist_y;
    }
    else
    {
        game->player.step_y = 1;
        game->map.delta_dist_y = (game->map.stack_size + 1.0 - game->player.player_y) * game->map.delta_dist_y;
    }
    while (game->map.hit_wall == 0)
    {
        if (game->map.delta_dist_x < game->map.delta_dist_y)
        {
            game->map.delta_dist_x += game->map.delta_dist_x;
            game->map.stack_size += game->player.step_x;
            game->map.side = 0;
        }
        else
        {
            game->map.delta_dist_y += game->map.delta_dist_y;
            game->map.stack_size += game->player.step_y;
            game->map.side = 1;
        }
        if (game->map.grid[game->map.stack_size][game->map.stack_size] == '1')
            game->map.hit_wall = 1;
    }
}

void draw_column(t_game *game, int x)
{
    unsigned int    line_height;
    unsigned int    draw_start;
    unsigned int    draw_end;
    unsigned int    y;
    int color;

    if (game->map.side == 0)
        game->map.perp_wall_dist = (game->map.stack_size - game->player.player_x + (1 - game->player.step_x) / 2) / game->player.ray_dir_x;
    else
        game->map.perp_wall_dist = (game->map.stack_size - game->player.player_y + (1 - game->player.step_y) / 2) / game->player.ray_dir_y;
    line_height = (int)(game->map.height / game->map.perp_wall_dist);
    draw_start = -line_height / 2 + game->map.height / 2;
    draw_end = line_height / 2 + game->map.height / 2;
    if (draw_end >= game->map.height)
        draw_end = game->map.height - 1;
    color = (game->map.side == 1) ? 0xAAAAAA : 0xFFFFFF;
    y = draw_start;
    while (y <= draw_end)
    {
        mlx_pixel_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y, color);
        y++;
    }
}

void render_frame(t_game *game)
{
    void *image;
    char *buffer;
    int bpp, size_line, endian, x;

    image = mlx_new_image(game->mlx.mlx_ptr, 800, 600);
    if (!image)
        exit(EXIT_FAILURE);
    buffer = mlx_get_data_addr(image, &bpp, &size_line, &endian);
    x = 0;
    while (x < 800)
    {
        calculate_ray(game, x);
        perform_dda(game);
        draw_column(game, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, image, 0, 0);
    mlx_destroy_image(game->mlx.mlx_ptr, image);
}