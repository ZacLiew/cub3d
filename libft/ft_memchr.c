/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:39:14 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/07 18:38:28 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cstr;
	size_t			index;

	str = (unsigned char *)s;
	cstr = (unsigned char) c;
	index = 0;
	while (index < n)
	{
		if (str[index] == cstr)
			return (str + index);
		index++;
	}
	return (NULL);
}
