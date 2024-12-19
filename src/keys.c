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
    if (key == XK_w)
        move_forward(game);
    /*if (key == XK_s)
        move_backward(game);
    if (key == XK_a)
        move_left(game);
    if (key == XK_d)
        move_right(game);
    if (key == XK_q)
        rotqte_right(game);
    if(key == XK_e)
        rotate_left(game);*/
    return (0);
}