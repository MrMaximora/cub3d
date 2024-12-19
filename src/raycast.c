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

void calculate_ray(t_game *game, int x)
{
    game->player.camera_x = 2 * x / (double)game->mlx.width_windows - 1.0;
    game->player.ray_dir_x = game->player.player_dir_x + game->player.plane_x * game->player.camera_x;
    game->player.ray_dir_y = game->player.player_dir_y + game->player.plane_y * game->player.camera_x;
    game->map.map_x = (int)game->player.player_x;
    game->map.map_y = (int)game->player.player_y;
    game->map.delta_dist_x = fabs(1 / game->player.ray_dir_x);
    game->map.delta_dist_y = fabs(1 / game->player.ray_dir_y);
    calculate_step_and_side_dist(game);
}

void calculate_step_and_side_dist(t_game *game)
{
    if (game->player.ray_dir_x < 0)
    {
        game->player.step_x = -1;
        game->map.side_dist_x = (game->player.player_x - game->map.map_x) * game->map.delta_dist_x;
    }
    else
    {
        game->player.step_x = 1;
        game->map.side_dist_x = (game->map.map_x + 1.0 - game->player.player_x) * game->map.delta_dist_x;
    }

    if (game->player.ray_dir_y < 0)
    {
        game->player.step_y = -1;
        game->map.side_dist_y = (game->player.player_y - game->map.map_y) * game->map.delta_dist_y;
    }
    else
    {
        game->player.step_y = 1;
        game->map.side_dist_y = (game->map.map_y + 1.0 - game->player.player_y) * game->map.delta_dist_y;
    }
}

void perform_dda(t_game *game)
{
    while (game->map.hit_wall == 0)
    {
        if (game->map.side_dist_x < game->map.side_dist_y)
        {
            game->map.side_dist_x += game->map.delta_dist_x;
            game->map.map_x += game->player.step_x;
            game->map.side = 0;
        }
        else
        {
            game->map.side_dist_y += game->map.delta_dist_y;
            game->map.map_y += game->player.step_y;
            game->map.side = 1;
        }
        if (game->map.grid[game->map.map_y][game->map.map_x] == '1')
            game->map.hit_wall = 1;
    }
    calculate_dist(game);
}

void calculate_dist(t_game *game)
{
    if (game->map.side == 0)
        game->map.perp_wall_dist = (game->map.map_x - game->player.player_x + (1 - game->player.step_x) / 2) / game->player.ray_dir_x;
    else
        game->map.perp_wall_dist = (game->map.map_y - game->player.player_y + (1 - game->player.step_y) / 2) / game->player.ray_dir_y;
    if (game->map.perp_wall_dist < 0) 
        game->map.perp_wall_dist = fabs(game->map.perp_wall_dist);
}

void calculate_wall_height(t_game *game)
{
    game->map.line_height = (int)(game->mlx.height_windows / game->map.perp_wall_dist);
    game->map.draw_start = (-game->map.line_height / 2) + (game->mlx.height_windows / 2);
    if (game->map.draw_start < 0)
        game->map.draw_start = 0;
    game->map.draw_end = (game->map.line_height / 2) + (game->mlx.height_windows / 2);
    if (game->map.draw_end >= game->mlx.height_windows)
        game->map.draw_end = game->mlx.height_windows - 1;
}

void render_frame(t_game *game)
{
    void *image;
    char *buffer;
    int bpp, size_line, endian;
    int x;

    image = mlx_new_image(game->mlx.mlx_ptr, game->mlx.width_windows, game->mlx.height_windows);
    if (!image)
        exit(EXIT_FAILURE);
    buffer = mlx_get_data_addr(image, &bpp, &size_line, &endian);
    if (!buffer)
        exit(EXIT_FAILURE);
    for (x = 0; x < game->mlx.width_windows; x++)
    {
        game->map.hit_wall = 0;
        calculate_ray(game, x);
        perform_dda(game);
        calculate_wall_height(game);
        draw_column(game, buffer, x);
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, image, 0, 0);
    mlx_destroy_image(game->mlx.mlx_ptr, image);
}

void draw_column(t_game *game, char *buffer, int x)
{
    int y;
    int ceiling_color = 0x87CEEB;
    int wall_color = 0xFF0000;
    int floor_color = 0x228B22;

    for (y = 0; y < game->map.draw_start; y++)
    {
        int pixel_pos = y * game->mlx.width_windows + x;
        if (pixel_pos >= 0 && pixel_pos < game->mlx.width_windows * game->mlx.height_windows)
        {
            buffer[pixel_pos * 4 + 0] = ceiling_color & 0xFF;         // Blue
            buffer[pixel_pos * 4 + 1] = (ceiling_color >> 8) & 0xFF;  // Green
            buffer[pixel_pos * 4 + 2] = (ceiling_color >> 16) & 0xFF; // Red
        }
    }
    for (y = game->map.draw_start; y <= game->map.draw_end; y++)
    {
        int pixel_pos = y * game->mlx.width_windows + x;
        if (pixel_pos >= 0 && pixel_pos < game->mlx.width_windows * game->mlx.height_windows)
        {
            buffer[pixel_pos * 4 + 0] = wall_color & 0xFF;         // Blue
            buffer[pixel_pos * 4 + 1] = (wall_color >> 8) & 0xFF;  // Green
            buffer[pixel_pos * 4 + 2] = (wall_color >> 16) & 0xFF; // Red
        }
    }
    for (y = game->map.draw_end + 1; y < game->mlx.height_windows; y++)
    {
        int pixel_pos = y * game->mlx.width_windows + x;
        if (pixel_pos >= 0 && pixel_pos < game->mlx.width_windows * game->mlx.height_windows)
        {
            buffer[pixel_pos * 4 + 0] = floor_color & 0xFF;         // Blue
            buffer[pixel_pos * 4 + 1] = (floor_color >> 8) & 0xFF;  // Green
            buffer[pixel_pos * 4 + 2] = (floor_color >> 16) & 0xFF; // Red
        }
    }
}
