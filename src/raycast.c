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
    game->player.camera_x = 2 * x / (double)game->map.width - 1;
    game->player.plane_x = -game->player.player_dir_y * 0.66;
    game->player.plane_y = game->player.player_dir_x * 0.66;
    game->player.ray_dir_x = game->player.player_dir_x + game->player.plane_x * game->player.camera_x;
    game->player.ray_dir_y = game->player.player_dir_y + game->player.plane_y * game->player.camera_x;
    game->map.delta_dist_x = fabs(1 / game->player.ray_dir_x);  
    game->map.delta_dist_y = fabs(1 / game->player.ray_dir_y);
}

void perform_dda(t_game *game)
{
    int map_x = (int)game->player.player_x;
    int map_y = (int)game->player.player_y;

    // Calculate step and initial side distance
    if (game->player.ray_dir_x < 0)
    {
        game->player.step_x = -1;
        game->map.side_dist_x = (game->player.player_x - map_x) * game->map.delta_dist_x;
    }
    else
    {
        game->player.step_x = 1;
        game->map.side_dist_x = (map_x + 1.0 - game->player.player_x) * game->map.delta_dist_x;
    }

    if (game->player.ray_dir_y < 0)
    {
        game->player.step_y = -1;
        game->map.side_dist_y = (game->player.player_y - map_y) * game->map.delta_dist_y;
    }
    else
    {
        game->player.step_y = 1;
        game->map.side_dist_y = (map_y + 1.0 - game->player.player_y) * game->map.delta_dist_y;
    }
    
    // Perform the DDA algorithm
    while (1)
    {
        if (game->map.side_dist_x < game->map.side_dist_y)
        {
            game->map.side_dist_x += game->map.delta_dist_x;
            map_x += game->player.step_x;
            game->map.side = 0; // Ray hits the X axis
        }
        else
        {
            game->map.side_dist_y += game->map.delta_dist_y;
            map_y += game->player.step_y;
            game->map.side = 1; // Ray hits the Y axis
        }

        // Ensure map coordinates are within bounds of the map row
        if (map_y < 0 || map_y >= game->map.height || map_x < 0 || map_x >= ft_strlen(game->map.grid[map_y]))
            return;

        // Check for wall collision
        if (game->map.grid[map_y][map_x] == '1') // Wall hit
        {
            // Calculate the perpendicular distance to the wall
            if (game->map.side == 0)
                game->map.perp_wall_dist = (map_x - game->player.player_x + (1 - game->player.step_x) / 2) / game->player.ray_dir_x;
            else
                game->map.perp_wall_dist = (map_y - game->player.player_y + (1 - game->player.step_y) / 2) / game->player.ray_dir_y;
            printf("Perpendicular distance: %f\n", game->map.perp_wall_dist);
            return;
        }
    }
}


void draw_column(t_game *game, char *buffer, int x)
{
    int line_height;
    int draw_start, draw_end;
    int color;

    // Ensure the x position is within valid bounds
    if (x < 0 || x >= game->mlx.width_windows) 
    {
        printf("Error: x (%d) out of bounds (0-%d)\n", x, game->mlx.width_windows - 1);
        return;
    }
    // Calculate the perpendicular wall distance and line height
    line_height = (int)(game->mlx.height_windows / game->map.perp_wall_dist);
    if (line_height > game->mlx.height_windows)
        line_height = game->mlx.height_windows;
    // Find the start and end points to draw the column
    draw_start = (-line_height / 2) + (game->mlx.height_windows / 2);
    draw_end = (line_height / 2) + (game->mlx.height_windows / 2);
    // Ensure the start and end points are within valid bounds
    if (draw_start < 0) 
        draw_start = 0;
    if (draw_end >= game->mlx.height_windows) 
        draw_end = game->mlx.height_windows - 1;
    // Debug information
    //printf("Line height: %d, Draw start: %d, Draw end: %d\n", line_height, draw_start, draw_end);
    // Set the color for the wall (change depending on side)
    color = (game->map.side == 1) ? 0xAAAAAA : 0xFFFFFF;
    // Draw the column
    for (int y = draw_start; y <= draw_end; y++)
    {
        int pixel_pos = y * game->mlx.width_windows + x;
        printf("Pixel position: %d, Y: %d, X: %d\n", pixel_pos, y, x);
        if (pixel_pos < 0 || pixel_pos >= game->mlx.width_windows * game->mlx.height_windows)
        {
            printf("Error: pixel_pos (%d) out of bounds. y=%d\n", pixel_pos, y);
            continue;
        }
        buffer[pixel_pos + 0] = color & 0xFF;         // Blue
        buffer[pixel_pos + 1] = (color >> 8) & 0xFF;  // Green
        buffer[pixel_pos + 2] = (color >> 16) & 0xFF; // Red
    }
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
    //printf("Buffer info - bpp: %d, size_line: %d, endian: %d\n", bpp, size_line, endian);
    x = 0;
    while (x < game->mlx.width_windows)
    {
        calculate_ray(game, x);
        perform_dda(game);
        draw_column(game, buffer, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, image, 0, 0);
    mlx_destroy_image(game->mlx.mlx_ptr, image);
}
