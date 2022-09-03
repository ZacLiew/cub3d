/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 15:13:12 by leu-lee           #+#    #+#             */
/*   Updated: 2021/06/09 23:41:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	numbers;
	size_t	index;
	int		negative;

	numbers = 0;
	index = 0;
	negative = 1;
	while (str[index] == 32 || (str[index] >= 9 && str[index] <= 13))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			negative = negative * -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		numbers = numbers * 10 + (str[index] - 48);
		index++;
	}
	return (numbers * negative);
}
