/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:45:37 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 17:46:55 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t	count, size_t	size)
{
	void	*heap;
	size_t	total_size;

	total_size = count * size;
	heap = malloc(total_size);
	if (!heap)
		return (NULL);
	ft_memset(heap, 0, total_size);
	return (heap);
}	
