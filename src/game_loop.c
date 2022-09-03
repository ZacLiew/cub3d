/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:23:59 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 15:49:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	display_string_for_door(t_mlx *mlx)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = mlx->player.x + mlx->player.dir_x;
	tmp_y = mlx->player.y + mlx->player.dir_y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D'
		|| mlx->map.board[(int)tmp_y][(int)tmp_x] == 'd')
		mlx_string_put(mlx->mlx, mlx->win, (WIN_WIDTH / 2) - 75,
			(WIN_HEIGHT / 2) + 30, 0x00FFFFFF, "Press 'E' to open/close");
}

int	game_loop(t_mlx *mlx)
{
	t_image	img;
	t_image	door;

	create_empty_img(&img, mlx, WIN_WIDTH, WIN_HEIGHT);
	create_empty_img(&door, mlx, WIN_WIDTH, WIN_HEIGHT);
	set_img_opacity(&door, 255);
	if (TEXTURE_FLOOR == 1)
		set_up_floor_ceiling(mlx, &img, 0);
	else
		default_floor_ceiling(mlx, &img);
	set_up_wall_raycasting(mlx, &img, &door);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, door.img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->hud.img, 200, 200);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cross.img,
		(WIN_WIDTH / 2) - 20, (WIN_HEIGHT / 2) - 20);
	display_string_for_door(mlx);
	draw_mini_map(mlx, 200, 0, 0);
	mlx_destroy_image(mlx->mlx, img.img);
	mlx_destroy_image(mlx->mlx, door.img);
	return (0);
}
