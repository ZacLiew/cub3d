/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:43:55 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 23:54:24 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	index;
	int		len;
	char	*heap;

	len = ft_strlen(s1) + ft_strlen(s2);
	heap = (char *)malloc(sizeof(char) * (len + 1));
	if (heap == NULL)
		return (NULL);
	index = 0;
	while (*s1)
	{
		heap[index] = *s1;
		s1++;
		index++;
	}
	while (*s2)
	{
		heap[index] = *s2;
		s2++;
		index++;
	}
	heap[index] = '\0';
	return (heap);
}
