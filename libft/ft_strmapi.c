/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:33:10 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 23:49:40 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	index;
	char	*heap;

	index = 0;
	len = ft_strlen(s);
	heap = (char *)malloc(sizeof(char) * (len + 1));
	if (!heap)
		return (NULL);
	while (index < len)
	{
		heap[index] = f(index, s[index]);
		index++;
	}
	heap[index] = '\0';
	return (heap);
}
