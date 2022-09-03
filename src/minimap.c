/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:34:53 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 16:37:55 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color	return_minimap_color(t_mlx *mlx, t_image *img, int row, int col)
{
	if ((img->x + 1) % (int)(img->width / 11) == 0
		|| (img->y + 1) % (int)(img->height / 11) == 0)
		return (declare_color(0, 0, 0, 100));
	else if (row == floor(mlx->player.y) && col == floor(mlx->player.x))
		return (declare_color(255, 255, 255, 100));
	else if (mlx->map.board[row][col] == '0')
		return (declare_color(64, 64, 64, 100));
	else if (mlx->map.board[row][col] == '1')
		return (declare_color(204, 0, 0, 100));
	else if (mlx->map.board[row][col] == 'D' || mlx->map.board[row][col] == 'd')
		return (declare_color(0, 0, 255, 100));
	return (declare_color(0, 0, 0, 100));
}

static void	get_minimap(t_mlx *mlx, t_image *img, int row)
{
	t_color	color;
	int		tmp_x;
	int		col;

	tmp_x = img->x;
	col = (floor(mlx->player.x) - 5) - 1;
	if (col < 0)
		col = 0;
	while (tmp_x >= 0)
	{
		tmp_x -= (int)(img->width / 11);
		col++;
		if (col >= mlx->map.col || row >= mlx->map.row)
		{
			color = declare_color(0, 0, 0, 100);
			insert_img_pixel_color(img, color);
			return ;
		}
	}
	color = return_minimap_color(mlx, img, row, col);
	insert_img_pixel_color(img, color);
}

void	draw_mini_map(t_mlx *mlx, int width_height, int x_pos, int y_pos)
{
	t_image	img;
	int		row;

	row = floor(mlx->player.y) - 5;
	if (row < 0)
		row = 0;
	create_empty_img(&img, mlx, width_height, width_height);
	set_img_opacity(&img, 255);
	img.y = 0;
	while (img.y++ < img.height)
	{
		img.x = 0;
		if (img.y % (int)(img.height / 11) == 0)
			row++;
		while (img.x++ < img.width)
		{
			if (((img.x - (img.width / 2)) * (img.x - (img.width / 2)))
				+ ((img.y - (img.height / 2)) * (img.y - (img.height / 2)))
				< (img.width / 2) * (img.width / 2))
				get_minimap(mlx, &img, row);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, x_pos, y_pos);
	mlx_destroy_image(mlx->mlx, img.img);
}
