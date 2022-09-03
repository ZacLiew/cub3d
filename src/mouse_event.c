/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:30:36 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 15:49:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	mouse_move(int x, int y, t_mlx *mlx)
{
	(void)y;
	if (x > WIN_WIDTH / 2)
		rotate(mlx, ROTATE_ANGLE);
	else if (x < WIN_WIDTH / 2)
		rotate(mlx, ROTATE_ANGLE * -1);
	mlx_mouse_move(mlx->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}
