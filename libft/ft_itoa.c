/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:55:11 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 23:36:21 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	if (n == 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*heap;
	size_t	len;
	long	num;

	num = (long)n;
	len = ft_len(num);
	heap = malloc(sizeof(char) * (len + 1));
	if (!heap)
		return (NULL);
	if (num == 0)
		heap[0] = '0';
	if (num < 0)
	{
		heap[0] = '-';
		num *= -1;
	}
	heap[len] = '\0';
	while (len-- != 0 && num > 0)
	{
		heap[len] = 48 + (num % 10);
		num = num / 10;
	}
	return (heap);
}
