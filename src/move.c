#include "../includes/cub3D.h"

void    move_forward(t_game *game)
{
    if (game->map.grid[(int)(game->player.player_y)][(int)(game->player.player_x + game->player.player_dir_x * game->player.move_speed)] != '1')
        game->player.player_x += game->player.player_dir_x * game->player.move_speed;
    if (game->map.grid[(int)(game->player.player_y + game->player.player_dir_y * game->player.move_speed)][(int)(game->player.player_x)] != '1')
        game->player.player_x += game->player.player_dir_y * game->player.move_speed;
}