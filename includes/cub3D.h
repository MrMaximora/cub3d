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
    unsigned int x;
    unsigned int y;
} t_point;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
} t_mlx;

typedef struct s_player
{
    int     player_x;
    int     player_y;
    int     step_x;
    int     step_y;
    char    player_dir;
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
    unsigned int    width;
    unsigned int    height;
    unsigned int    stack_size;
    unsigned int    top;
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
unsigned int	ft_strlen(char *str);
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
void    ft_solver_fill(t_game *game, unsigned int start_x, unsigned int start_y);
int     ft_last_verif(t_game *game);
int     is_closed(t_game *game, unsigned int new_x, unsigned int new_y);
void    print_map(t_map *map);
void    calculate_ray(t_game *game, int x);
void    perform_dda(t_game *game);
int     handle_keys(int key, t_game *game);
void    render_frame(t_game *game);
void    draw_column(t_game *game, int x);

#endif
