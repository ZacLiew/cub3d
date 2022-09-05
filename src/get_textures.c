/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:35:22 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/05 15:48:57 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	free(line);
	return (1);
}

void	check_floor_ceiling(char *line, int len, int number, int count)
{
	int	i;

	i = 0;
	if (count == 6)
		call_error("-Error: Too many arguments parsed-\n");
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || len == 0)
		return ;
	if (ft_isdigit(line[i]) == 0 && line[i] != ',')
		call_error("-Error: Invalid char parsing error-\n");
	if (ft_isdigit(line[i]) == 1 && number == 0)
	{
		while (ft_isdigit(line[i]) == 1)
			i++;
		number = 1;
	}
	else if (line[i++] == ',' && number == 1)
		number = 0;
	else
		call_error("Error: Floor or ceiling parsing error\n");
	if (len > 0)
		check_floor_ceiling(line + i, len - i, number, count + 1);
}

void	set_floor_ceiling(t_mlx *mlx, char **array)
{
	int	i;

	i = 1;
	while (i <= 3)
	{
		if (ft_atoi(array[i]) > 255 || ft_atoi(array[i]) < 0)
			call_error("Error: Invalid floor/ceiling RGB range\n");
		i++;
	}
	if (array[0][0] == 'F')
	{
		mlx->color_floor = declare_color(ft_atoi(array[1]), ft_atoi(array[2]),
				ft_atoi(array[3]), 0);
	}
	if (array[0][0] == 'C')
	{
		mlx->color_ceiling = declare_color(ft_atoi(array[1]), ft_atoi(array[2]),
				ft_atoi(array[3]), 0);
	}
	free_str_array(array);
}

void	set_textures(t_mlx *mlx, char *line, char **array, int i)
{
	char	*tmp;

	tmp = remove_newline(array[1]);
	if (i < 4 && array[1] != NULL && array[2] != NULL && array[2][0] != '\n')
		call_error("Error: Invalid chars after directional textures\n");
	printf("|%s|\n", tmp);
	if ((ft_strncmp(array[0], "NO", 3) == 0) && i == 0)
		mlx->north = get_xpm_img(mlx, tmp);
	else if ((ft_strncmp(array[0], "SO", 3) == 0) && i == 1)
		mlx->south = get_xpm_img(mlx, tmp);
	else if ((ft_strncmp(array[0], "WE", 3) == 0) && i == 2)
		mlx->west = get_xpm_img(mlx, tmp);
	else if ((ft_strncmp(array[0], "EA", 3) == 0) && i == 3)
		mlx->east = get_xpm_img(mlx, tmp);
	else if (((ft_strncmp(array[0], "F", 2) == 0) && i == 4)
		|| ((ft_strncmp(array[0], "C", 2) == 0) && i == 5))
	{
		check_floor_ceiling(line + 1, ft_strlen(line + 1) - 1, 0, 0);
		comma_to_space(line);
		array = ft_split(line, ' ');
		set_floor_ceiling(mlx, array);
	}
	else
		call_error("Error: No required arguments/Not following strict order-\n");
	free(tmp);
}

int	get_textures(t_mlx *mlx, int fd)
{
	char		*line;
	char		**array;
	static int	i;
	static int	count;

	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			call_error("Error: Incomplete inputs\n");
		count++;
		if (check_empty_line(line))
			continue ;
		array = ft_split(line, ' ');
		set_textures(mlx, line, array, i);
		i++;
		free_str_array(array);
		free(line);
		printf("Flags passed -> %d\n", i);
	}
	close(fd);
	return (count);
}
