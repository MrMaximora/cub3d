/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:30:42 by maxouvra          #+#    #+#             */
/*   Updated: 2024/12/10 16:30:44 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int handle_keys(int key, t_game *game)
{
    if (key == XK_Escape)
		exit_prog(game);
    if (key == XK_w)
        game->player.move_forward = 1;
    if (key == XK_s)
        game->player.move_backward = 1;
    if (key == XK_a)
        game->player.strafe_left = 1;
    if (key == XK_d)
        game->player.strafe_right = 1;
    if (key == XK_q)
        game->player.rotate_right = 1;
    if(key == XK_e)
        game->player.rotate_left = 1;
    return (0);
}

int handle_keys_release(int key, t_game *game)
{
    if (key == XK_w)
        game->player.move_forward = 0;
    if (key == XK_s)
        game->player.move_backward = 0;
    if (key == XK_a)
        game->player.strafe_left = 0;
    if (key == XK_d)
        game->player.strafe_right = 0;
    if (key == XK_q)
        game->player.rotate_right = 0;
    if(key == XK_e)
        game->player.rotate_left = 0;
    return (0);
}

void    update_player_pos(t_game *game)
{
    if (game->player.move_forward)
        move_forward(game);
    if (game->player.move_backward)
        move_backward(game);
    if (game->player.strafe_left)
        strafe_left(game);
    if (game->player.strafe_right)
        strafe_right(game);
    if (game->player.rotate_left)
        rotate_left(game);
    if (game->player.rotate_right)
        rotate_right(game);
}