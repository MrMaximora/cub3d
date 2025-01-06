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
    int x;

    x = 0;
    while (x < game->mlx.width_windows)
    {
        game->map.hit_wall = 0;
        calculate_ray(game, x);
        perform_dda(game);
        calculate_wall_height(game);
        draw_column(game, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->map.image.img, 0, 0);
}

/*void draw_column(t_game *game, char *buffer, int x)
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
}*/

void    my_mlx_pixel_put(t_texture *texture, int x, int y, int color)
{
    char    *dst;

    dst = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_column(t_game *game, int x)
{
    int tex_x;
    int tex_y;
    t_texture wall_texture;
    int y;
    int color;
    // int d; // Distance from the top of the screen to the current pixel
    double wall_x;

    if (game->map.side == 0 && game->player.step_x > 0)
        wall_texture = game->map.texture_wall_n;
    else if (game->map.side == 0 && game->player.step_x < 0)
        wall_texture = game->map.texture_wall_s;
    else if (game->map.side == 1 && game->player.step_y > 0)
        wall_texture = game->map.texture_wall_e;
    else if (game->map.side == 1 && game->player.step_y < 0)
        wall_texture = game->map.texture_wall_w;

    if (game->map.side == 0)
        wall_x = game->player.player_y + game->map.perp_wall_dist * game->player.ray_dir_y;
    else
        wall_x = game->player.player_x + game->map.perp_wall_dist * game->player.ray_dir_x;
    wall_x -= floor(wall_x); // Remove the integer part to get the fractional part
/*    tex_x = (int)(wall_x * (double)(wall_texture.width - 1));
    if ((game->map.side == 0 && game->player.ray_dir_x > 0) || (game->map.side == 1 && game->player.ray_dir_y < 0))
        tex_x = wall_texture.width - tex_x - 1;
    y = game->map.draw_start;
    while (y < game->map.draw_end)
    {
        d = y * 256 - game->mlx.height_windows * 128 + game->map.line_height * 128;
        tex_y = ((d * wall_texture.height) / game->map.line_height) / 256;
        color = wall_texture.data[wall_texture.width * tex_y + tex_x];
        my_mlx_pixel_put(&game->map.image, x, y, color);
        y++;
    }*/
    tex_x = (int)(wall_x * 160.f);
    if ((game->map.side == 0 && game->player.ray_dir_x > 0) || (game->map.side == 1
            && game->player.ray_dir_y < 0))
        tex_x = 160.f - tex_x - 1;
    double step = 1.0 * 160.f / game->map.line_height;
    double tex_pos = (game->map.draw_start - game->mlx.height_windows / 2 + game->map.line_height / 2) * step;
    y = game->map.draw_start - 1;
    while (++y < game->map.draw_end)
    {
        tex_y = (int)tex_pos & (160 - 1);
        tex_pos += step;
        // color = wall_texture.data[wall_texture.width * tex_y + tex_x];
        color = wall_texture.data[160 * tex_y * 4 + \
        (tex_x - wall_texture.width + 1) * 4] << 16 | \
        wall_texture.data[160 * tex_y * 4 + (tex_x - \
        wall_texture.width + 1) * 4 + 1] << 8 | wall_texture.data[160 * tex_y * \
        4 + (tex_x - wall_texture.width + 1) * 4 + 2];
        // my_mlx_pixel_put(cb->image, x, y + 1, ray->color);
        my_mlx_pixel_put(&game->map.image, x, y, color);
    }
    // Draw the floor and ceiling
    y = 0;
    while (y < game->map.draw_start)
    {
        my_mlx_pixel_put(&game->map.image, x, y, game->map.cap_color);
        y++;
    }
    y = game->map.draw_end;
    while (y < game->mlx.height_windows)
    {
        my_mlx_pixel_put(&game->map.image, x, y, game->map.floor_color);
        y++;
    }
}
