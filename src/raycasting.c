/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:01:00 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 15:49:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cam_set_up(t_mlx *mlx, t_cam *cam)
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
		cam->side_dist_x = (cam->map_x + 1 - mlx->player.x) * cam->delta_dist_x;
	}
	if (cam->ray_dir_y < 0)
	{
		cam->step_y = -1;
		cam->side_dist_y = (mlx->player.y - cam->map_y) * cam->delta_dist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->side_dist_y = (cam->map_y + 1 - mlx->player.y) * cam->delta_dist_y;
	}
}

static void	calculate_wall_height(t_mlx *mlx, t_cam *cam, t_wall *wall)
{
	if (cam->map_x < mlx->map.col && cam->map_y < mlx->map.row)
	{
		if (cam->side == 0)
			cam->wall_dist = (cam->map_x - mlx->player.x
					+ (1 - cam->step_x) / 2) / cam->ray_dir_x;
		else
			cam->wall_dist = (cam->map_y - mlx->player.y
					+ (1 - cam->step_y) / 2) / cam->ray_dir_y;
		wall->height = (int)(WIN_HEIGHT / cam->wall_dist);
		wall->start = WIN_HEIGHT / 2 - wall->height / 2;
		if (wall->start < 0)
			wall->start = 0;
		wall->end = WIN_HEIGHT / 2 + wall->height / 2;
		if (wall->end >= WIN_HEIGHT)
			wall->end = WIN_HEIGHT - 1;
	}
}

static void	distance_from_player_to_wall(t_mlx *mlx, t_cam *cam,
	t_wall *wall, t_image *door)
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
			calculate_wall_height(mlx, cam, wall);
			get_wall_texture(wall, door, cam, mlx);
		}
	}
}

void	set_up_wall_raycasting(t_mlx *mlx, t_image *img, t_image *door)
{
	t_cam	cam;
	t_wall	wall;

	cam.x = 0;
	while (cam.x < WIN_WIDTH)
	{
		cam.camera_x = 2 * cam.x / (double)WIN_WIDTH - 1;
		cam.map_x = (int)mlx->player.x;
		cam.map_y = (int)mlx->player.y;
		cam.hit = 0;
		cam_set_up(mlx, &cam);
		distance_from_player_to_wall(mlx, &cam, &wall, door);
		calculate_wall_height(mlx, &cam, &wall);
		get_wall_texture(&wall, img, &cam, mlx);
		cam.x++;
	}
}
