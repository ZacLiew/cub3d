/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:41:05 by zhliew            #+#    #+#             */
/*   Updated: 2022/08/26 16:07:24 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_minimap_background_color(t_mlx *mlx, t_image *img, t_color *color, int row)
{
	int tmp_x;
	int col;

	col = floor(mlx->player.x) - 5;
	if (col < 0)
		col = 0;
	col--;
	tmp_x = img->x;
	*color = declare_color(0, 0, 0, 100);
	while (tmp_x >= 0)
	{
		tmp_x -= (int)(img->width / 11);
		col++;
		if (col >= mlx->map.col || row >= mlx->map.row)
			return ;
	}
	if (mlx->map.board[row][col] == '0')
		*color = declare_color(64,64,64, 100);
	else if (mlx->map.board[row][col] == '1')
		*color = declare_color(204,0,0, 100);
	else if (mlx->map.board[row][col] == 'D' || mlx->map.board[row][col] == 'd')
		*color = declare_color(0,0,255, 100);
	if (row == floor(mlx->player.y) && col == floor(mlx->player.x))
		*color = declare_color(255,255,255, 100);
	if ((img->x + 1) % (int)(img->width / 11) == 0
		|| (img->y + 1) % (int)(img->height / 11) == 0)
		*color = declare_color(0, 0, 0, 100);
}

void	draw_mini_map(t_mlx *mlx, int width, int height, int x_pos, int y_pos)
{
	t_color color;
	t_image img;
	int row;
	
	row = floor(mlx->player.y) - 5;
	if (row < 0)
		row = 0;
	create_empty_img(&img, mlx, width, height);
	set_img_opacity(&img, 255);
	img.y = 0;
	while (img.y < img.height)
	{
		img.x = 0;
		while (img.x < img.width)
		{
			if (((img.x - (width / 2)) * (img.x - (width / 2))) +
				((img.y - (height / 2)) * (img.y - (height / 2))) < (width / 2) * (width / 2))
			{
				get_minimap_background_color(mlx, &img, &color, row);
				insert_img_pixel_color(&img, color);
			}
			img.x++;
		}
		img.y++;
		if (img.y % (int)(img.height / 11) == 0)
			row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, x_pos, y_pos);
	mlx_destroy_image(mlx->mlx, img.img);
}

t_image	get_wall_img(t_mlx *mlx, t_cam *cam)
{
	if (mlx->map.board[cam->map_y][cam->map_x] == 'D')
		return (mlx->door);
	else if (cam->side == 0)
	{
		if (cam->ray_dir_x > 0)
			return (mlx->west);
		else
			return (mlx->east);
	}
	else
	{
		if (cam->ray_dir_y < 0)
			return (mlx->north);
		else
			return (mlx->south);
	}
}

t_resize	set_up_wall_resize_ratio(t_mlx *mlx, t_image *img, t_cam *cam, t_wall *wall)
{
	t_resize ratio;

	if (cam->side == 0)
		ratio.wall_x_pos = mlx->player.y + cam->wall_dist * cam->ray_dir_y;
	else
		ratio.wall_x_pos = mlx->player.x + cam->wall_dist * cam->ray_dir_x;
	ratio.wall_x_pos -= floor(ratio.wall_x_pos);
	ratio.tex_x = (int)(ratio.wall_x_pos * (double)img->width);
	if (cam->side == 0 && cam->ray_dir_x > 0)
		ratio.tex_x  = img->width - ratio.tex_x  - 1;
	if (cam->side == 1 && cam->ray_dir_y < 0)
		ratio.tex_x  = img->width - ratio.tex_x  - 1;
	ratio.step_y  = (double)img->height / (double)wall->height;
	ratio.wall_y_pos = (wall->start - WIN_HEIGHT / 2 + wall->height / 2) * ratio.step_y;
	return (ratio);
}

void	get_wall_texture(t_wall *wall, t_image *img, int x, t_cam *cam, t_mlx *mlx)
{
	t_color color;
	t_image wall_img;
	t_resize ratio;

	img->y = 0;
	img->x = x;
	wall_img = get_wall_img(mlx, cam);
	ratio = set_up_wall_resize_ratio(mlx, &wall_img, cam, wall);
	while (img->y < WIN_HEIGHT)
	{
		if (img->y >= wall->start && img->y <= wall->end)
		{
			ratio.tex_y = (int)ratio.wall_y_pos;
			if (ratio.tex_y >= wall_img.height)
				ratio.tex_y = wall_img.height - 1;
			ratio.wall_y_pos += ratio.step_y;
			color = get_img_pixel_color(&wall_img, ratio.tex_x, ratio.tex_y);
			if (mlx->map.board[cam->map_y][cam->map_x] == 'D' && color.red == -1 && color.green == -1 && color.blue == -1)
				color.opacity = -1;
			insert_img_pixel_color(img, color);
		}
		img->y++;
	}
}

t_resize	set_up_ground_resize_ratio(t_mlx *mlx, int y)
{
	t_resize ratio;
	double ray_dir_x0;
	double ray_dir_y0;
	double ray_dir_x1;
	double ray_dir_y1;
	double posZ;
	double row_dis;
	int pos;

	ray_dir_x0 = mlx->player.dir_x - mlx->player.plane_x;
	ray_dir_y0 = mlx->player.dir_y - mlx->player.plane_y;
	ray_dir_x1 = mlx->player.dir_x + mlx->player.plane_x;
	ray_dir_y1 = mlx->player.dir_y + mlx->player.plane_y;
	pos = y - (WIN_HEIGHT / 2);
	posZ = 0.5 * WIN_HEIGHT;
	row_dis = posZ / pos;
	ratio.step_x = row_dis * (ray_dir_x1 - ray_dir_x0) / WIN_WIDTH;
	ratio.step_y = row_dis * (ray_dir_y1 - ray_dir_y0) / WIN_WIDTH;
	ratio.wall_x_pos = mlx->player.x + row_dis * ray_dir_x0;
	ratio.wall_y_pos = mlx->player.y + row_dis * ray_dir_y0;
	return (ratio);
}

void	set_up_floor_ceiling(t_mlx *mlx, t_image *img)
{
	int y;
	t_resize ratio;
	t_color color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		ratio = set_up_ground_resize_ratio(mlx, y);
		img->x = 0;
		while (img->x < WIN_WIDTH)
		{
			img->y = y;
			ratio.tex_x = (int)(mlx->ground.width * (ratio.wall_x_pos - (int)ratio.wall_x_pos));
			ratio.tex_y = (int)(mlx->ground.height * (ratio.wall_y_pos - (int)ratio.wall_y_pos));
			ratio.wall_x_pos += ratio.step_x;
			ratio.wall_y_pos += ratio.step_y;
			color = get_img_pixel_color(&mlx->ground, ratio.tex_x, ratio.tex_y);
			insert_img_pixel_color(img, color);
			img->y = WIN_HEIGHT - img->y - 1;
			insert_img_pixel_color(img, color);
			img->x++;
		}
		y++;
	}
}

void	calculate_wall_height(t_mlx *mlx, t_cam *cam, t_wall *wall)
{
	if (cam->map_x < mlx->map.col && cam->map_y < mlx->map.row)
	{
		if (cam->side == 0)
			cam->wall_dist = (cam->map_x - mlx->player.x + (1 - cam->step_x) / 2) / cam->ray_dir_x;
		else
			cam->wall_dist = (cam->map_y - mlx->player.y + (1 - cam->step_y) / 2) / cam->ray_dir_y;
		wall->height = (int)(WIN_HEIGHT / cam->wall_dist);
		wall->start = WIN_HEIGHT / 2 - wall->height / 2;
		if (wall->start < 0)
			wall->start = 0;
		wall->end = WIN_HEIGHT / 2 + wall->height / 2;
		if (wall->end >= WIN_HEIGHT)
			wall->end = WIN_HEIGHT - 1;
	}
}

void	cam_set_up(t_mlx *mlx, t_cam *cam)
{
	cam->ray_dir_x = mlx->player.dir_x + mlx->player.plane_x * cam->camera_x;
	cam->ray_dir_y = mlx->player.dir_y + mlx->player.plane_y * cam->camera_x;
	cam->delta_dist_x = fabs(1 / cam->ray_dir_x);
	cam->delta_dist_y = fabs(1 / cam->ray_dir_y);
	if (cam->ray_dir_x < 0)
	{
		cam->step_x = -1;
		cam->side_dist_x = (mlx->player.x - cam->map_x) * cam->delta_dist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->side_dist_x = (cam->map_x + 1.0 - mlx->player.x) * cam->delta_dist_x;
	}
	if (cam->ray_dir_y < 0)
	{
		cam->step_y = -1;
		cam->side_dist_y = (mlx->player.y - cam->map_y) * cam->delta_dist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->side_dist_y = (cam->map_y + 1.0 - mlx->player.y) * cam->delta_dist_y;
	}
}

void	distance_from_player_to_wall(t_mlx *mlx, t_cam *cam, t_wall *wall, t_image *door, int x)
{
	while (cam->hit == 0)
	{
		if (cam->side_dist_x < cam->side_dist_y)
		{
			cam->side_dist_x += cam->delta_dist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		}
		else
		{
			cam->side_dist_y += cam->delta_dist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (cam->map_x >= mlx->map.col || cam->map_y >= mlx->map.row)
			break ;
		else if (mlx->map.board[cam->map_y][cam->map_x] == '1')
			cam->hit = 1;
		else if (mlx->map.board[cam->map_y][cam->map_x] == 'D')
		{
			calculate_wall_height(mlx, cam , wall);
			get_wall_texture(wall, door, x, cam, mlx);
		}
	}
}


void	set_up_wall(t_mlx *mlx, t_image *img, t_image *door)
{
	t_cam	cam;
	t_wall	wall;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		cam.map_x = (int)mlx->player.x;
		cam.map_y = (int)mlx->player.y;
		cam.hit = 0;
		cam_set_up(mlx, &cam);
		distance_from_player_to_wall(mlx, &cam, &wall, door, x);
		calculate_wall_height(mlx, &cam , &wall);
		get_wall_texture(&wall, img, x, &cam, mlx);
		x++;
	}
}

void	default_floor_ceiling(t_mlx *mlx, t_image *img)
{
	t_color color;

	color = mlx->color_ceiling;
	img->y = 0;
	while (img->y < img->height)
	{
		img->x = 0;
		while (img->x < img->width)
		{
			insert_img_pixel_color(img, color);
			img->x++;
		}
		img->y++;
		if (img->y >= img->height / 2)
			color = mlx->color_floor;
	}
}

void	display_string_for_door(t_mlx *mlx)
{
	double tmp_x;
	double tmp_y;

	tmp_x = mlx->player.x + mlx->player.dir_x;
	tmp_y = mlx->player.y + mlx->player.dir_y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D' || mlx->map.board[(int)tmp_y][(int)tmp_x] == 'd')
		mlx_string_put(mlx->mlx, mlx->win, (WIN_WIDTH / 2) - 75, (WIN_HEIGHT / 2) + 30, 0x00FFFFFF, "Press 'E' to open/close");
}


int	raycasting(t_mlx *mlx)
{
	t_image	img;
	t_image door;

	create_empty_img(&img, mlx, WIN_WIDTH, WIN_HEIGHT);
	create_empty_img(&door, mlx, WIN_WIDTH, WIN_HEIGHT);
	set_img_opacity(&door, 255);
	if (TEXTURE_FLOOR == 1)
		set_up_floor_ceiling(mlx, &img);
	else
		default_floor_ceiling(mlx, &img);
	set_up_wall(mlx, &img, &door);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, door.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->hud.img, 200, 200);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cross.img, (WIN_WIDTH / 2) - 20 , (WIN_HEIGHT / 2) - 20);
	display_string_for_door(mlx);
	draw_mini_map(mlx, 200, 200, 0, 0);
	mlx_destroy_image(mlx->mlx, img.img);
	mlx_destroy_image(mlx->mlx, door.img);
	return (0);
}

void	rotate(t_mlx *mlx, double angle)
{
	double tmp;

	tmp = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(angle) - mlx->player.dir_y * sin(angle);
	mlx->player.dir_y = tmp * sin(angle) + mlx->player.dir_y * cos(angle);
	tmp = mlx->player.plane_x;
	mlx->player.plane_x = mlx->player.plane_x * cos(angle) - mlx->player.plane_y * sin(angle);
	mlx->player.plane_y = tmp * sin(angle) + mlx->player.plane_y * cos(angle);
}

void	movement(t_mlx *mlx, double x, double y)
{
	double tmp_x;
	double tmp_y;

	tmp_x = mlx->player.x + x;
	tmp_y = mlx->player.y + y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] != '1' && mlx->map.board[(int)tmp_y][(int)tmp_x] != 'D')
	{
		mlx->player.x += x;
		mlx->player.y += y;
	}
}

void	exit_game()
{
	system("pkill afplay");
	exit(0);
}

void	open_close_door(t_mlx *mlx)
{
	double tmp_x;
	double tmp_y;

	tmp_x = mlx->player.x + mlx->player.dir_x;
	tmp_y = mlx->player.y + mlx->player.dir_y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D' || mlx->map.board[(int)tmp_y][(int)tmp_x] == 'd')
	{
		system("afplay sound/open1.wav&");
		if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D')
			mlx->map.board[(int)tmp_y][(int)tmp_x] = 'd';
		else
			mlx->map.board[(int)tmp_y][(int)tmp_x] = 'D';
	}
}

int		key_pressed(int keycode, t_mlx *mlx)
{
	int speed;

	speed = 10;
	if (keycode == ESC)
		exit_game();
	if (keycode == KEY_A)
		movement(mlx, (mlx->player.plane_x / speed) * -1, (mlx->player.plane_y / speed) * -1);
	if (keycode == KEY_D)
		movement(mlx, (mlx->player.plane_x / speed), (mlx->player.plane_y / speed));
	if (keycode == KEY_W)
		movement(mlx, (mlx->player.dir_x / speed), (mlx->player.dir_y / speed));
	if (keycode == KEY_S)
		movement(mlx, (mlx->player.dir_x / speed) * -1, (mlx->player.dir_y / speed) * -1);
	if (keycode == RIGHT)
		rotate(mlx, ROTATE_ANGLE * -1);
	if (keycode == LEFT)
		rotate(mlx, ROTATE_ANGLE);
	if (keycode == KEY_E)
		open_close_door(mlx);
	return (0);
}

int		mouse_move(int x, int y, t_mlx *mlx)
{
	(void)y;

	if (x > WIN_WIDTH / 2)
		rotate(mlx, ROTATE_ANGLE);
	else if (x < WIN_WIDTH / 2)
		rotate(mlx, ROTATE_ANGLE * -1);
	mlx_mouse_move(mlx->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

static int	hook_close(t_mlx *mlx)
{
	(void)mlx;
	exit_game();
	return (0);
}

void	player_direction(t_mlx *mlx, char c)
{
	mlx->player.dir_x = 0;
	mlx->player.dir_y = 0;
	mlx->player.plane_x = 0;
	mlx->player.plane_y = 0;
	if (c == 'N')
	{
		mlx->player.dir_y = -1;
		mlx->player.plane_x = 0.66;
	}
	else if (c == 'S')
	{
		mlx->player.dir_y = 1;
		mlx->player.plane_x = -0.66;
	}
	else if (c == 'W')
	{
		mlx->player.dir_x = 1;
		mlx->player.plane_y = 0.66;
	}
	else if (c == 'E')
	{
		mlx->player.dir_x = -1;
		mlx->player.plane_y = -0.66;
	}
}

int	mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		system("afplay sound/fire.wav&");
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->muzzle.img, 635, 565);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->hud.img, 200, 200);
	}
	return (0);
}

int	main(void)
{
	t_mlx mlx;

	int x;
	int y = 0;
	int tmp = 0;
	char buff[220];
	int fd = open("maps/map.cur", O_RDONLY);
	read(fd, buff, 220);
	mlx.map.board = malloc(sizeof(char *) * 20);
	while (y < 20)
	{
		x = 0;
		mlx.map.board[y] = malloc(sizeof(char) * 11);
		while (x < 10)
		{
			mlx.map.board[y][x] = buff[tmp];
			x++;
			tmp++;
		}
		y++;
		tmp++;
	}
	system("afplay sound/back.mp3&");
	mlx.map.row = 20;
	mlx.map.col = 10;
	mlx.player.x = 4.5;
	mlx.player.y = 4.5;
	player_direction(&mlx, 'N');
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	mlx.north = get_xpm_img(&mlx, "texture/1.xpm");
	mlx.south = get_xpm_img(&mlx, "texture/2.xpm");
	mlx.west = get_xpm_img(&mlx, "texture/3.xpm");
	mlx.east = get_xpm_img(&mlx, "texture/6.xpm");
	mlx.ground = get_xpm_img(&mlx, "texture/4.xpm");
	mlx.door = get_xpm_img(&mlx, "texture/door.xpm");
	mlx.hud = get_xpm_img(&mlx, "texture/hud.xpm");
	mlx.cross = get_xpm_img(&mlx, "texture/crosshair.xpm");
	mlx.muzzle = get_xpm_img(&mlx, "texture/muzzle.xpm");
	mlx.color_ceiling = declare_color(255, 0, 0, 0);
	mlx.color_floor = declare_color(0, 255, 0, 0);
	mlx_mouse_hide();
	mlx_hook(mlx.win, 2, 0, key_pressed, &mlx);
	mlx_hook(mlx.win, 17, 0, hook_close, &mlx);
	mlx_hook(mlx.win, 6, 0, mouse_move, &mlx);
	mlx_hook(mlx.win, 4, 0, mouse_press, &mlx);
	mlx_loop_hook(mlx.mlx, raycasting, &mlx);
	mlx_loop(mlx.mlx);
	system("pkill afplay");
	return (0);
}