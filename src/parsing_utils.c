/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:00:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/05 08:48:24 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*remove_newline(char *str)
{
	char	*tmp;

	if (str[ft_strlen(str) - 1] == '\n')
	{
		tmp = ft_strndup(str, ft_strlen(str) - 1);
		return (tmp);
	}
	else
		tmp = ft_strdup(str);
	return (tmp);
}

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
	printf("data->map_h: %d\n", mlx->map.col);
	while (mlx->map.board[i] != NULL)
	{
		printf("|%s|\n", mlx->map.board[i]);
		i++;
	}
}
