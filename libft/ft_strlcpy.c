/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:28:42 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/08 17:29:08 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dst, const char *src, size_t size )
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	if (!src && !dst)
		return (0);
	while (src[count] != '\0')
		count++;
	if (size > 0)
	{
		while (src[index] != '\0' && index < (size - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (count);
}
