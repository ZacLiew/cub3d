/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:17:20 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 17:47:29 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	index;
	char	*array;

	len = ft_strlen(s);
	array = malloc(sizeof(char) * len + 1);
	if (!array)
		return (NULL);
	index = 0;
	while (index < len + 1)
	{
		array[index] = s[index];
		index++;
	}
	return (array);
}
