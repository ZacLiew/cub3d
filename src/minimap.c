/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:34:53 by zhliew            #+#    #+#             */
/*   Updated: 2022/08/27 10:53:42 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_minimap_background_color(t_mlx *mlx, t_image *img,
	t_color *color, int row)
{
	int	tmp_x;
	int	col;

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
		*color = declare_color(64, 64, 64, 100);
	else if (mlx->map.board[row][col] == '1')
		*color = declare_color(204, 0, 0, 100);
	else if (mlx->map.board[row][col] == 'D' || mlx->map.board[row][col] == 'd')
		*color = declare_color(0, 0, 255, 100);
	if (row == floor(mlx->player.y) && col == floor(mlx->player.x))
		*color = declare_color(255, 255, 255, 100);
	if ((img->x + 1) % (int)(img->width / 11) == 0
		|| (img->y + 1) % (int)(img->height / 11) == 0)
		*color = declare_color(0, 0, 0, 100);
}

void	draw_mini_map(t_mlx *mlx, int width_height, int x_pos, int y_pos)
{
	t_color	color;
	t_image	img;
	int		row;

	row = floor(mlx->player.y) - 5;
	if (row < 0)
		row = 0;
	create_empty_img(&img, mlx, width_height, width_height);
	set_img_opacity(&img, 255);
	img.y = 0;
	while (img.y < img.height)
	{
		img.x = 0;
		while (img.x < img.width)
		{
			if (((img.x - (img.width / 2)) * (img.x - (img.width / 2)))
				+ ((img.y - (img.height / 2)) * (img.y - (img.height / 2)))
				< (img.width / 2) * (img.width / 2))
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
