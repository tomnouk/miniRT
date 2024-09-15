/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:49:23 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/16 01:08:11 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_color	mult_colors(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r / 255;
	res.g = a.g * b.g / 255;
	res.b = a.b * b.b / 255;
	return (res);
}

t_color	sum_colors(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_color	mult_color_ratio(t_color a, double ratio)
{
	t_color	res;

	res.r = a.r * ratio;
	res.g = a.g * ratio;
	res.b = a.b * ratio;
	return (res);
}
