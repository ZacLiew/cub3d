/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:00:59 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/05 16:13:40 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_char_valid(t_mlx *mlx, char c, int i, int y)
{
	static int	dir;

	if (c != '1' && c != '0'
		&& c != 'N' && c != 'W'
		&& c != 'S' && c != 'E'
		&& c != ' ' && c != 'D')
		call_error("Error: Not a valid char\n");
	if (c == 'D')
	{
		if (((mlx->map.board[y][i + 1] == '1')
			&& (mlx->map.board[y][i - 1] == '1'))
			|| ((mlx->map.board[y - 1][i] == '1')
			&& (mlx->map.board[y + 1][i] == '1')))
			;
		else
			call_error("Error: Door is not inbetween two walls");
	}
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		mlx->player.x = (double)i + 0.5;
		mlx->player.y = (double)y + 0.5;
		player_direction(mlx, c);
		dir++;
	}
	return (dir);
}

void	check_inner_wall(t_mlx *mlx, int i, int y)
{
	if ((y - 1 >= 0) && (i - 1 >= 0))
	{
		if (y != (mlx->map.row - 1))
		{
			if ((mlx->map.board[y + 1][i] != '1')
				&& (mlx->map.board[y + 1][i] != ' '))
				call_error("Error: Map not valid (Floor next to space)\n");
		}
		if (((mlx->map.board[y][i + 1] != '1')
			&& (mlx->map.board[y][i + 1] != ' ')
			&& (mlx->map.board[y][i + 1] != '\0')) ||
			((mlx->map.board[y][i - 1] != '1')
			&& (mlx->map.board[y][i - 1] != ' ')) ||
			((mlx->map.board[y - 1][i] != '1')
			&& (mlx->map.board[y - 1][i] != ' ')))
			call_error("Error: Map not valid (Floor next to space)\n");
	}
}

int	check_horizontal_wall(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] != '1' && str[i] != ' ')
			call_error("Error: Map not valid (Horizontal wall)\n");
		i++;
	}
	return (0);
}

int	check_vertical_wall(t_mlx *mlx)
{
	int	i;
	int	len;

	i = 0;
	while (i < mlx->map.row)
	{
		len = ft_strlen(mlx->map.board[i]);
		if (*(mlx->map.board)[0] != '1' || *(mlx->map.board)[0] != ' ')
		{
			if (mlx->map.board[i][len - 1] != ' ')
				call_error("Error: Map not valid (Vertical wall)\n");
		}
		i++;
	}
	return (0);
}

int	check_map_valid(t_mlx *mlx)
{
	int	i;
	int	y;
	int	ret;

	y = 0;
	while (mlx->map.board[y] != NULL)
	{
		i = 0;
		while (mlx->map.board[y][i])
		{
			ret = check_char_valid(mlx, mlx->map.board[y][i], i, y);
			if (mlx->map.board[y][i] == ' ')
				check_inner_wall(mlx, i, y);
			i++;
		}
		y++;
	}
	check_horizontal_wall(mlx->map.board[0]);
	check_horizontal_wall(mlx->map.board[mlx->map.row - 1]);
	check_vertical_wall(mlx);
	return (ret);
}
