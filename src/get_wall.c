/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:03:33 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 15:49:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_image	get_wall_img(t_mlx *mlx, t_cam *cam)
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

static t_resize	set_up_wall_resize_ratio(t_mlx *mlx, t_image *img,
	t_cam *cam, t_wall *wall)
{
	t_resize	ratio;

	if (cam->side == 0)
		ratio.wall_x_pos = mlx->player.y + cam->wall_dist * cam->ray_dir_y;
	else
		ratio.wall_x_pos = mlx->player.x + cam->wall_dist * cam->ray_dir_x;
	ratio.wall_x_pos -= floor(ratio.wall_x_pos);
	ratio.tex_x = (int)(ratio.wall_x_pos * (double)img->width);
	if (cam->side == 0 && cam->ray_dir_x > 0)
		ratio.tex_x = img->width - ratio.tex_x - 1;
	if (cam->side == 1 && cam->ray_dir_y < 0)
		ratio.tex_x = img->width - ratio.tex_x - 1;
	ratio.step_y = (double)img->height / (double)wall->height;
	ratio.wall_y_pos = (wall->start - WIN_HEIGHT / 2 + wall->height / 2)
		* ratio.step_y;
	return (ratio);
}

void	get_wall_texture(t_wall *wall, t_image *img, t_cam *cam, t_mlx *mlx)
{
	t_color		color;
	t_image		wall_img;
	t_resize	ratio;

	img->y = 0;
	img->x = cam->x;
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
			if (mlx->map.board[cam->map_y][cam->map_x] == 'D' && color.red == -1
				&& color.green == -1 && color.blue == -1)
				color.opacity = -1;
			insert_img_pixel_color(img, color);
		}
		img->y++;
	}
}
