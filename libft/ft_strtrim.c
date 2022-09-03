/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:15:23 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 17:48:52 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	front;
	size_t	end;
	char	*heap;

	heap = NULL;
	if (s1 != NULL && set != NULL)
	{
		front = 0;
		end = ft_strlen(s1);
		while (s1[front] && ft_strchr(set, s1[front]))
			front++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > front)
			end--;
		heap = malloc(sizeof(char) * (end - front + 1));
		if (!heap)
			return (NULL);
		ft_strlcpy(heap, &s1[front], end - front + 1);
	}
	return (heap);
}
