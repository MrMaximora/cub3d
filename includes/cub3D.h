/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:10 by maxouvra          #+#    #+#             */
/*   Updated: 2024/11/14 10:21:12 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_point
{
    int y;
    int x;
} t_point;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     height_windows;
    int     width_windows;
} t_mlx;

typedef struct s_player
{
    double    player_x;
    double    player_y;
    int     step_x;
    int     step_y;
    char    player_dir;
    double  player_dir_x;
    double  player_dir_y;
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    double  plane_x;
    double  plane_y;
    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_map
{
    char            **grid;
    int             width;
    int             height;
    int             stack_size;
    int             top;
    int             line_height;
    int             draw_start;
    int             draw_end;
    int             map_y;
    int             map_x;
    double          side_dist_x;
    double          side_dist_y;
    double          delta_dist_x;
    double          delta_dist_y;
    double          perp_wall_dist;
    int             side;
    int             hit_wall;

}   t_map;

typedef struct s_game
{
    t_map       map;
    t_player    player;
    t_mlx       mlx;
}   t_game;


void	ft_error(char *str);
void    init_game(t_game *game);
void	ft_parser_map(t_game *game, char **av);
char	*ft_strnstr(char *str, char *to_find, int len);
int	    ft_strlen(char *str);
char	*ft_strdup(char *s);
void    ft_init_map(t_map *map);
void    ft_read_map(t_game *game, int fd);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char    **ft_realloc(char **old, int new_size);
char	*gnl(int fd);
size_t	ft_strlen_gnl(const char *str);
int     is_valid_char(char c);
int     validate_map(t_game *game);
void    ft_solver_fill(t_game *game, int start_y, int start_x);
int     ft_last_verif(t_game *game);
int     is_closed(t_game *game, int new_y, int new_x);
void    print_map(t_game *game);
void    calculate_ray(t_game *game, int x);
void    perform_dda(t_game *game);
int     handle_keys(int key, t_game *game);
void    render_frame(t_game *game);
void    draw_column(t_game *game, char *buffer, int x);
void    calculate_wall_height(t_game *game);
void    calculate_dist(t_game *game);
void    calculate_step_and_side_dist(t_game *game);
void    move_forward(t_game *game);

#endif
