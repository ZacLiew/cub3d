/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:19:16 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/07 23:03:46 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dstlen;
	unsigned int	srclen;
	size_t			index;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen + size);
	if (size <= dstlen)
		srclen = srclen + size;
	else
		srclen = srclen + dstlen;
	index = 0;
	while (src[index] != '\0' && (dstlen + index) < size - 1)
	{
		dst[dstlen + index] = src[index];
		index++;
	}
	dst[dstlen + index] = '\0';
	return (srclen);
}
