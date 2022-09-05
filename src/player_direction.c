/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:35:45 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/05 16:20:24 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		mlx->player.dir_x = -1;
		mlx->player.plane_y = -0.66;
	}
	else if (c == 'E')
	{
		mlx->player.dir_x = 1;
		mlx->player.plane_y = 0.66;
	}
}
