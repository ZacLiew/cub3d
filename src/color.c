/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:49:13 by zhliew            #+#    #+#             */
/*   Updated: 2022/08/27 10:32:29 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_color	declare_color(int red, int green, int blue, int opacity)
{
	t_color	color;

	color.red = red;
	color.green = green;
	color.blue = blue;
	color.opacity = opacity;
	return (color);
}
