/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:30:07 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 22:40:25 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	*ptr_d;
	unsigned char	*ptr_s;

	if (!dst && !src)
		return (NULL);
	index = 0;
	ptr_d = (unsigned char *)dst;
	ptr_s = (unsigned char *)src;
	while (index < n)
	{
		ptr_d[index] = ptr_s[index];
		if ((ptr_d[index]) == (unsigned char)c)
			return (dst + index + 1);
		index++;
	}
	return (NULL);
}
