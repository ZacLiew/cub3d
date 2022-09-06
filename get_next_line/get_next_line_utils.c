/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:17:18 by zhliew            #+#    #+#             */
/*   Updated: 2022/09/06 15:17:29 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index] != '\0')
		index++;
	return (index);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*heap;
	size_t	index;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		len = 0;
	if (len > strlen)
		len = strlen - start;
	heap = (char *)malloc(sizeof(char) * len + 1);
	if (!heap)
		return (NULL);
	index = 0;
	while (index < len)
	{
		heap[index] = s[start];
		index++;
		start++;
	}
	heap[index] = '\0';
	return (heap);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	index;
	char	*array;

	len = ft_strlen(str);
	array = (char *)malloc(sizeof(char) * len + 1);
	if (!array)
		return (NULL);
	index = 0;
	while (index < len)
	{
		array[index] = str[index];
		index++;
	}
	array[index] = '\0';
	return (array);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	int		len;
	char	*heap;

	len = ft_strlen(s1) + ft_strlen(s2);
	heap = malloc(sizeof(char) * (len + 1));
	if (!heap)
		return (NULL);
	index = 0;
	while (*s1)
	{
		heap[index] = *s1;
		index++;
		s1++;
	}
	while (*s2)
	{
		heap[index] = *s2;
		index++;
		s2++;
	}
	heap[index] = '\0';
	return (heap);
}

int	ft_strchr_gnl(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}
