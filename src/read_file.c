/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:54:22 by leu-lee           #+#    #+#             */
/*   Updated: 2022/09/05 15:14:49 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*allign_map_width(char *line, int len)
{
	int		i;
	char	*str;

	if (len == 0)
		return (line);
	i = 0;
	while (i < len)
	{
		str = ft_strjoin(line, " ");
		i++;
		free(line);
		line = str;
	}
	return (str);
}

void	get_map_padding(t_mlx *mlx, char *line, int i)
{
	char		*str;
	char		*tmp;

	if (line[ft_strlen(line) - 1] == '\n')
	{
		tmp = ft_strndup(line, ft_strlen(line) - 1);
		free(line);
		str = allign_map_width(tmp, mlx->map.col - ft_strlen(tmp));
	}
	else
		str = allign_map_width(line, mlx->map.col - ft_strlen(line));
	mlx->map.board[i] = ft_strndup(str, ft_strlen(str));
	free(str);
}

void	read_map(t_mlx *mlx, int fd, int skip)
{
	static int		j;
	static int		i;
	char			*line;

	while (1)
	{
		line = get_next_line(fd);
		if (j < skip)
		{
			free(line);
			j++;
			continue ;
		}
		if (line == NULL)
			break ;
		get_map_padding(mlx, line, i);
		i++;
	}
	mlx->map.board[i] = NULL;
	free(line);
	close(fd);
}

void	get_map_size(t_mlx *mlx, char **argv, int skip)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		mlx->map.row++;
		if (mlx->map.col < (int)ft_strlen(line))
			mlx->map.col = ft_strlen(line);
		free(line);
	}
	mlx->map.row -= skip;
	free(line);
	close(fd);
}

void	read_file(t_mlx *mlx, char **argv)
{
	int			fd;
	int			skip;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		call_error("Error: Not an existing map\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) != 0)
		call_error("Error: Not a .cub file\n");
	skip = get_textures(mlx, fd);
	get_map_size(mlx, argv, skip);
	mlx->map.board = (char **)malloc(sizeof(char *) * mlx->map.row + 1);
	fd = open(argv[1], O_RDONLY);
	read_map(mlx, fd, skip);
	print_map(mlx);
	if (check_map_valid(mlx) == 1)
		ft_putstr_fd("Map Initialized\n", 1);
	else
		call_error("Error: Wrong number of players\n");
}
