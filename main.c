/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:41:05 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/06 15:16:40 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_game(void)
{
	system("pkill afplay");
	exit(0);
}

static int	hook_close(t_mlx *mlx)
{
	(void)mlx;
	exit_game();
	return (0);
}

static void	init_cub3d(t_mlx *mlx)
{
	mlx->map.col = 0;
	mlx->map.row = 0;
	mlx->ground = get_xpm_img(mlx, "texture/ground.xpm");
	mlx->door = get_xpm_img(mlx, "texture/door.xpm");
	mlx->hud = get_xpm_img(mlx, "texture/hud.xpm");
	mlx->cross = get_xpm_img(mlx, "texture/crosshair.xpm");
	mlx->muzzle = get_xpm_img(mlx, "texture/muzzle.xpm");
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		call_error("Wrong argument number passed to program.\n");
	mlx.mlx = mlx_init();
	init_cub3d(&mlx);
	read_file(&mlx, argv);
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	mlx.map.board[(int)mlx.player.y][(int)mlx.player.x] = '0';
	system("afplay sound/back.mp3&");
	mlx_mouse_hide();
	mlx_hook(mlx.win, 2, 0, key_pressed, &mlx);
	mlx_hook(mlx.win, 17, 0, hook_close, &mlx);
	mlx_hook(mlx.win, 6, 0, mouse_move, &mlx);
	mlx_hook(mlx.win, 4, 0, mouse_press, &mlx);
	mlx_loop_hook(mlx.mlx, game_loop, &mlx);
	mlx_loop(mlx.mlx);
	system("pkill afplay");
	return (0);
}
