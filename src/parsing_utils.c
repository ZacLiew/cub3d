/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:00:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/03 15:33:34 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	check_parsed_value(t_data *data)
// {
// 	printf("North|%s|\n", data->tex.north);
// 	printf("South|%s|\n", data->tex.south);
// 	printf("West|%s|\n", data->tex.west);
// 	printf("East|%s|\n", data->tex.east);
// 	printf("~Ceiling~\n");
// 	printf("Red|%d|\n", data->ceiling.red);
// 	printf("Green|%d|\n", data->ceiling.green);
// 	printf("Blue|%d|\n", data->ceiling.blue);
// 	printf("~Floor~\n");
// 	printf("Red|%d|\n", data->floor.red);
// 	printf("Green|%d|\n", data->floor.green);
// 	printf("Blue|%d|\n", data->floor.blue);
// }

void	comma_to_space(char *line)
{
	while (*line)
	{
		if (*line == ',')
			*line = ' ';
		line++;
	}
}

void	free_str_array(char **str)
{
	char	**tmp;

	tmp = str;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(str);
}

void	call_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	print_map(t_mlx *mlx)
{
	int	i;

	i = 0;
	printf("|Printing map|\n");
	printf("data->map_h: %d\n", mlx->map.row);
	while (mlx->map.board[i] != NULL)
	{
		printf("|%s|\n", mlx->map.board[i]);
		i++;
	}
}
