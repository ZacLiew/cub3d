/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:41:05 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/03 16:49:32 by leu-lee          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_mlx mlx;
	(void)argc;

	// int x;
	// int y = 0;
	// int tmp = 0;
	// char buff[220];
	//map
	// int fd = open("maps/map.cur", O_RDONLY);
	// read(fd, buff, 220);
	// mlx.map.board = malloc(sizeof(char *) * 20);
	// while (y < 20)
	// {
	// 	x = 0;
	// 	mlx.map.board[y] = malloc(sizeof(char) * 11);
	// 	while (x < 10)
	// 	{
	// 		mlx.map.board[y][x] = buff[tmp];
	// 		x++;
	// 		tmp++;
	// 	}
	// 	y++;
	// 	tmp++;
	// }
	// mlx.map.row = 20;
	// mlx.map.col = 10;
	// mlx.player.x = 4.5;
	// mlx.player.y = 4.5;
	// player_direction(&mlx, 'N');
	mlx.mlx = mlx_init();
	read_file(&mlx, argv); // reads and print map
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	// get_textures and colors
	// mlx.north = get_xpm_img(&mlx, "texture/1.xpm");
	// mlx.south = get_xpm_img(&mlx, "texture/2.xpm");
	// mlx.west = get_xpm_img(&mlx, "texture/3.xpm");
	// mlx.east = get_xpm_img(&mlx, "texture/6.xpm");
	// mlx.color_ceiling = declare_color(255, 0, 0, 0);
	// mlx.color_floor = declare_color(0, 255, 0, 0);

	mlx.ground = get_xpm_img(&mlx, "texture/ground.xpm");
	mlx.door = get_xpm_img(&mlx, "texture/door.xpm");
	mlx.hud = get_xpm_img(&mlx, "texture/hud.xpm");
	mlx.cross = get_xpm_img(&mlx, "texture/crosshair.xpm");
	mlx.muzzle = get_xpm_img(&mlx, "texture/muzzle.xpm");

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