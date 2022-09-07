/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:42:16 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/06 15:00:15 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include "get_next_line.h"
# include "libft.h"
# include "styling.h"
# include "../mlx/mlx.h"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_E 14
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define ROTATE_ANGLE 0.08
# define TEXTURE_FLOOR 0

typedef struct s_resize
{
	double	step_x;
	double	wall_x_pos;
	int		tex_x;
	double	step_y;
	double	wall_y_pos;
	int		tex_y;
}				t_resize;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_cam
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_dist;
	int		hit;
	int		step_x;
	int		step_y;
	int		side;
	int		x;
}				t_cam;

typedef struct s_map
{
	char	**board;
	int		row;
	int		col;
}				t_map;

typedef struct s_wall
{
	int	height;
	int	start;
	int	end;
}				t_wall;

typedef struct s_image
{
	int		width;
	int		height;
	int		bpp;
	int		stride;
	int		endian;
	int		x;
	int		y;
	void	*img;
	char	*img_data;
}				t_image;

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
	int	opacity;
}				t_color;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_image		north;
	t_image		west;
	t_image		south;
	t_image		east;
	t_image		ground;
	t_image		door;
	t_image		hud;
	t_image		cross;
	t_image		muzzle;
	t_player	player;
	t_color		color_ceiling;
	t_color		color_floor;
}				t_mlx;

typedef struct s_floor
{
	double		ray_dir_x0;
	double		ray_dir_y0;
	double		ray_dir_x1;
	double		ray_dir_y1;
	double		pos_z;
	double		row_dis;
	int			pos;
}				t_floor;

t_color	declare_color(int red, int green, int blue, int opacity);
void	create_empty_img(t_image *img, t_mlx *mlx, int width, int height);
void	insert_img_pixel_color(t_image *img, t_color color);
void	set_img_opacity(t_image *img, int opacity);
t_color	get_img_pixel_color(t_image *img, int x, int y);
t_image	get_xpm_img(t_mlx *mlx, char *file);
void	exit_game(void);
void	rotate(t_mlx *mlx, double angle);
int		key_pressed(int keycode, t_mlx *mlx);
int		mouse_move(int x, int y, t_mlx *mlx);
int		mouse_press(int button, int x, int y, t_mlx *mlx);
void	draw_mini_map(t_mlx *mlx, int width_height, int x_pos, int y_pos);
void	default_floor_ceiling(t_mlx *mlx, t_image *img);
void	set_up_floor_ceiling(t_mlx *mlx, t_image *img, int y);
void	set_up_wall_raycasting(t_mlx *mlx, t_image *img, t_image *door);
void	get_wall_texture(t_wall *wall, t_image *img, t_cam *cam, t_mlx *mlx);
int		game_loop(t_mlx *mlx);

/* Parsing files */
void	read_file(t_mlx *mlx, char **argv);
int		get_textures(t_mlx *mlx, int fd);
int		check_map_valid(t_mlx *mlx);
void	player_direction(t_mlx *mlx, char c);

char	*remove_newline(char *str);
void	call_error(char *msg);
void	free_str_array(char **str);
void	comma_to_space(char *line);
void	print_map(t_mlx *mlx);

#endif