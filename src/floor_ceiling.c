/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:54:48 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/05 14:24:16 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	default_floor_ceiling(t_mlx *mlx, t_image *img)
{
	t_color	color;

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

static t_resize	set_up_floor_ceiling_resize_ratio(t_mlx *mlx, int y)
{
	t_resize	ratio;
	t_floor		floor;

	floor.ray_dir_x0 = mlx->player.dir_x - mlx->player.plane_x;
	floor.ray_dir_y0 = mlx->player.dir_y - mlx->player.plane_y;
	floor.ray_dir_x1 = mlx->player.dir_x + mlx->player.plane_x;
	floor.ray_dir_y1 = mlx->player.dir_y + mlx->player.plane_y;
	floor.pos = y - (WIN_HEIGHT / 2);
	floor.pos_z = 0.5 * WIN_HEIGHT;
	floor.row_dis = floor.pos_z / floor.pos;
	ratio.step_x = floor.row_dis * (floor.ray_dir_x1 - floor.ray_dir_x0)
		/ WIN_WIDTH;
	ratio.step_y = floor.row_dis * (floor.ray_dir_y1 - floor.ray_dir_y0)
		/ WIN_WIDTH;
	ratio.wall_x_pos = mlx->player.x + floor.row_dis * floor.ray_dir_x0;
	ratio.wall_y_pos = mlx->player.y + floor.row_dis * floor.ray_dir_y0;
	return (ratio);
}

void	set_up_floor_ceiling(t_mlx *mlx, t_image *img, int y)
{
	t_resize	ratio;
	t_color		color;

	while (y < WIN_HEIGHT)
	{
		ratio = set_up_floor_ceiling_resize_ratio(mlx, y);
		img->x = 0;
		while (img->x < WIN_WIDTH)
		{
			img->y = y;
			ratio.tex_x = (int)(mlx->ground.width
					* (ratio.wall_x_pos - (int)ratio.wall_x_pos));
			ratio.tex_y = (int)(mlx->ground.height
					* (ratio.wall_y_pos - (int)ratio.wall_y_pos));
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
