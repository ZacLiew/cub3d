/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:28:58 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/05 16:48:03 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_mlx *mlx, double angle)
{
	double	tmp;

	tmp = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(angle)
		- mlx->player.dir_y * sin(angle);
	mlx->player.dir_y = tmp * sin(angle) + mlx->player.dir_y * cos(angle);
	tmp = mlx->player.plane_x;
	mlx->player.plane_x = mlx->player.plane_x * cos(angle)
		- mlx->player.plane_y * sin(angle);
	mlx->player.plane_y = tmp * sin(angle) + mlx->player.plane_y * cos(angle);
}

static void	movement(t_mlx *mlx, double x, double y)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = mlx->player.x + x;
	tmp_y = mlx->player.y + y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] != '1'
		&& mlx->map.board[(int)tmp_y][(int)tmp_x] != 'D')
	{
		mlx->player.x += x;
		mlx->player.y += y;
	}
}

static void	open_close_door(t_mlx *mlx)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = mlx->player.x + mlx->player.dir_x;
	tmp_y = mlx->player.y + mlx->player.dir_y;
	if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D'
		|| mlx->map.board[(int)tmp_y][(int)tmp_x] == 'd')
	{
		system("afplay sound/open1.wav&");
		if (mlx->map.board[(int)tmp_y][(int)tmp_x] == 'D')
			mlx->map.board[(int)tmp_y][(int)tmp_x] = 'd';
		else
			mlx->map.board[(int)tmp_y][(int)tmp_x] = 'D';
	}
}

int	key_pressed(int keycode, t_mlx *mlx)
{
	int	speed;

	speed = 10;
	if (keycode == ESC)
		exit_game();
	if (keycode == KEY_A)
		movement(mlx, (mlx->player.plane_x / speed) * -1,
			(mlx->player.plane_y / speed) * -1);
	if (keycode == KEY_D)
		movement(mlx, (mlx->player.plane_x / speed),
			(mlx->player.plane_y / speed));
	if (keycode == KEY_W)
		movement(mlx, (mlx->player.dir_x / speed),
			(mlx->player.dir_y / speed));
	if (keycode == KEY_S)
		movement(mlx, (mlx->player.dir_x / speed) * -1,
			(mlx->player.dir_y / speed) * -1);
	if (keycode == RIGHT)
		rotate(mlx, ROTATE_ANGLE);
	if (keycode == LEFT)
		rotate(mlx, ROTATE_ANGLE * -1);
	if (keycode == KEY_E)
		open_close_door(mlx);
	return (0);
}
