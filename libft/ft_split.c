/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:12:57 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 23:02:16 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(const char *s, char c)
{
	size_t	index;
	size_t	words;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		if (s[index] != '\0')
			words++;
		while (s[index] && s[index] != c)
			index++;
	}
	return (words);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	index;

	if (!src && !dst)
		return (0);
	index = 0;
	while (src[index] != '\0' && index < n)
	{
		dst[index] = src[index];
		++index;
	}
	while (index < n)
	{
		dst[index] = '\0';
		index++;
	}
	return (dst);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * n + 1);
	if (!str)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

char	**ft_split(const char *s, char c)
{
	char	**table;
	size_t	index;
	size_t	count;
	size_t	startpos;

	index = 0;
	count = 0;
	table = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!table)
		return (NULL);
	while (s[index])
	{
		while (s[index] == c)
			index++;
		startpos = index;
		while (s[index] && s[index] != c)
			index++;
		if (index > startpos)
		{
			table[count] = ft_strndup(s + startpos, index - startpos);
			count++;
		}
	}
	table[count] = NULL;
	return (table);
}
