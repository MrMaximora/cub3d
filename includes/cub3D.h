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
	int	y;
	int	x;
}	t_point;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height_windows;
	int		width_windows;
}	t_mlx;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	int		step_x;
	int		step_y;
	int		move_forward;
	int		move_backward;
	int		strafe_left;
	int		strafe_right;
	int		rotate_left;
	int		rotate_right;
	char	player_dir;
	float	player_dir_x;
	float	player_dir_y;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	rot_speed;
}	t_player;

typedef struct s_texture
{
	int				height;
	int				width;
	int				bpp;
	int				endian;
	int				size_line;
	void			*img;
	unsigned char	*data;
}	t_texture;

typedef struct s_map
{
	char		**grid;
	char		*path_texture_wall_n;
	char		*path_texture_wall_s;
	char		*path_texture_wall_e;
	char		*path_texture_wall_w;
	t_texture	texture_wall_n;
	t_texture	texture_wall_s;
	t_texture	texture_wall_e;
	t_texture	texture_wall_w;
	int			cap_color;
	int			floor_color;
	int			width;
	int			height;
	int			stack_size;
	int			top;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			map_y;
	int			map_x;
	int			n_textures;
	int			n_colors;
	int			r;
	int			g;
	int			b;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		perp_wall_dist;
	int			side;
	int			hit_wall;
	int			tex_x;
	int			tex_y;
	float		wall_x;
	float		step;
	int			bpp;
	int			constant_column;
	int			total_texture_size;
	t_texture	image;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
}	t_game;

void	init_game(t_game *game);
void	ft_parser_map(t_game *game, char **av);
char	*ft_strnstr(char *str, char *to_find, int len);
int		ft_strlen(char *str);
char	*ft_strdup(char *s);
void	ft_read_map(t_game *game, int fd);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_realloc(char **old, int new_size);
char	*gnl(int fd);
size_t	ft_strlen_gnl(const char *str);
int		is_valid_char(char c);
int		validate_map(t_game *game);
void	ft_solver_fill(t_game *game, int start_y, int start_x);
int		ft_last_verif(t_game *game);
int		is_closed(t_game *game, int new_y, int new_x);
void	calculate_ray(t_game *game, int x);
void	perform_dda(t_game *game);
int		handle_keys(int key, t_game *game);
void	render_frame(t_game *game);
void	draw_wall(t_game *game, int x);
void	calculate_wall_height(t_game *game);
void	calculate_dist(t_game *game);
void	calculate_step_and_side_dist(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		handle_keys_release(int key, t_game *game);
void	update_player_pos(t_game *game);
void	free_map(t_map *map);
int		exit_prog(t_game *game);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_atoi(char *str);
int		ft_split_len(char **split);
char	**ft_split(char *s, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, size_t start, size_t len);
void	free_split(char **split);
void	parse_config(t_game *game, int fd);
void	assign_texture(t_game *game, char *identifier, char *path);
void	assign_color(t_game *game, char *identifier, char *value);
void	parse_line(t_game *game, char *line);
void	load_texture(t_game *game, t_texture *texture, char *file_path);
void	load_textures(t_game *game);
char	*ft_strndup(char *s, int n);
void	calculate_for_texture(t_game *game, t_texture *actual_wall);
int		place_player(t_game	*game, char c, int x, int y);
void	attribute(t_game *game, char c);

#endif
