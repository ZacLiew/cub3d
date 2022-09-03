/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:12:20 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 15:49:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_empty_img(t_image *img, t_mlx *mlx, int width, int height)
{
	img->width = width;
	img->height = height;
	img->y = 0;
	img->img = mlx_new_image(mlx->mlx, width, height);
	img->img_data = mlx_get_data_addr(img->img, &img->bpp,
			&img->stride, &img->endian);
	img->bpp /= 8;
}

void	insert_img_pixel_color(t_image *img, t_color color)
{
	int	i;

	i = (img->x * 4) + (img->y * img->stride);
	img->img_data[i++] = (char)color.blue;
	img->img_data[i++] = (char)color.green;
	img->img_data[i++] = (char)color.red;
	img->img_data[i] = (char)color.opacity;
}

void	set_img_opacity(t_image *img, int opacity)
{
	t_color	color;

	img->y = 0;
	while (img->y < img->height)
	{
		img->x = 0;
		while (img->x < img->width)
		{
			color = declare_color(0, 0, 0, opacity);
			insert_img_pixel_color(img, color);
			img->x++;
		}
		img->y++;
	}
}

t_color	get_img_pixel_color(t_image *img, int x, int y)
{
	t_color	color;
	int		i;

	if (x > img->width)
		x = img->width;
	else if (x < 0)
		x = 0;
	if (y > img->height)
		y = img->height;
	else if (y < 0)
		y = 0;
	i = (x * 4) + (y * img->stride);
	color.blue = img->img_data[i++];
	color.green = img->img_data[i++];
	color.red = img->img_data[i++];
	color.opacity = img->img_data[i];
	return (color);
}

t_image	get_xpm_img(t_mlx *mlx, char *file)
{
	t_image	img;

	if (open(file, O_RDONLY) < 0)
	{
		printf("\033[0;31m%s could not be open\n\033[0m", file);
		exit_game();
	}
	img.img = mlx_xpm_file_to_image(mlx->mlx, file, &img.width, &img.height);
	img.img_data = mlx_get_data_addr(img.img, &img.bpp,
			&img.stride, &img.endian);
	img.bpp /= 8;
	return (img);
}
