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
    game->map.stack_size = (int)game->player.player_x;
    game->map.top = (int)game->player.player_y;
    game->map.delta_dist_x = fabs(1 / game->player.ray_dir_x);
    game->map.delta_dist_y = fabs(1 / game->player.ray_dir_y);
    printf("ray_dir_x: %f, ray_dir_y: %f, player_dir_x: %f, player_dir_y: %f, plane_x: %f, plane_y: %f, camera_x: %f\n", 
           game->player.ray_dir_x, game->player.ray_dir_y, 
           game->player.player_dir_x, game->player.player_dir_y, 
           game->player.plane_x, game->player.plane_y, 
           game->player.camera_x);
}

void perform_dda(t_game *game)
{
    int map_x = (int)game->player.player_x;
    int map_y = (int)game->player.player_y;

    // Step and initial side distance initialization based on ray direction
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

    // Perform Digital Differential Analysis (DDA)
    game->map.hit_wall = 0;
    while (game->map.hit_wall == 0)
    {
        // Choose whether to step in the X direction or the Y direction
        if (game->map.side_dist_x < game->map.side_dist_y)
        {
            game->map.side_dist_x += game->map.delta_dist_x;
            map_x += game->player.step_x;
            game->map.side = 0; // Hit vertical wall
        }
        else
        {
            game->map.side_dist_y += game->map.delta_dist_y;
            map_y += game->player.step_y;
            game->map.side = 1; // Hit horizontal wall
        }

        // Check if the ray has hit a wall
        if (game->map.grid[map_y][map_x] == '1')  // Wall detected
        {
            game->map.hit_wall = 1;
        }
        // If you hit the edge of the map, break the loop
        if ((unsigned int)map_x >= game->map.width || (unsigned int)map_y >= game->map.height)
        {
            printf("Ray went out of bounds at (%d, %d)\n", map_x, map_y);
            game->map.hit_wall = 1; // Break the loop
        }
    }

    // Final map coordinates where the ray hit the wall
    game->map.stack_size = map_x;  // Final X map coordinate
    game->map.top = map_y;         // Final Y map coordinate

    // Optional: Debugging output to see the results
    printf("Hit wall at (%d, %d), side: %d\n", map_x, map_y, game->map.side);
}



void draw_column(t_game *game, char *buffer, int x)
{
    unsigned int line_height;
    unsigned int draw_start, draw_end;
    unsigned int y;
    int color;

    if (game->map.side == 0)
        game->map.perp_wall_dist = (game->map.stack_size - game->player.player_x + (1 - game->player.step_x) / 2) / game->player.ray_dir_x;
    else
        game->map.perp_wall_dist = (game->map.top - game->player.player_y + (1 - game->player.step_y) / 2) / game->player.ray_dir_y;

    line_height = (int)(game->map.height / game->map.perp_wall_dist);
    draw_start = -line_height / 2 + game->map.height / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + game->map.height / 2;
    if (draw_end >= game->map.height)
        draw_end = game->map.height - 1;

    color = (game->map.side == 1) ? 0xAAAAAA : 0xFFFFFF; // Adjust color based on wall side
    for (y = draw_start; y <= draw_end; y++)
    {
        unsigned int pixel_pos = y * game->map.width * 4 + x * 4;
        if (pixel_pos < game->map.width * game->map.height * 4) // Bounds check
        {
            buffer[pixel_pos + 0] = color & 0xFF;         // Blue
            buffer[pixel_pos + 1] = (color >> 8) & 0xFF;  // Green
            buffer[pixel_pos + 2] = (color >> 16) & 0xFF; // Red
        }
    }
}


void render_frame(t_game *game)
{
    void *image;
    char *buffer;
    int bpp, size_line, endian;
    unsigned int x;

    image = mlx_new_image(game->mlx.mlx_ptr, game->map.width, game->map.height);
    if (!image)
        exit(EXIT_FAILURE);
    buffer = mlx_get_data_addr(image, &bpp, &size_line, &endian);
    if (!buffer)
        exit(EXIT_FAILURE);
    x = 0;
    while (x < game->map.width)
    {
        calculate_ray(game, x);
        perform_dda(game);
        draw_column(game, buffer, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, image, 0, 0);
    mlx_destroy_image(game->mlx.mlx_ptr, image);
}
