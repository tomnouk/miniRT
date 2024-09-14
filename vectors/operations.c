/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:50:54 by sdell-er          #+#    #+#             */
/*   Updated: 2024/09/14 01:26:23 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_vector	axes_sum(t_axes a, t_axes b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	axes_sub(t_axes a, t_axes b)
{
	t_vector	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

double	vect_length2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vect_length(t_vector v)
{
	return (sqrt(vect_length2(v)));
}

double	angle(t_vector a, t_vector b)
{
	double	len_a;
	double	len_b;

	len_a = vect_length(a);
	len_b = vect_length(b);
	if (len_a == 0 || len_b == 0)
		return (0);
	return (acos(dot_product(a, b) / (len_a * len_b)));
}

double	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vector	vect_mult(t_vector v, double a)
{
	t_vector	res;

	res.x = v.x * a;
	res.y = v.y * a;
	res.z = v.z * a;
	return (res);
}

t_vector	normalize(t_vector v)
{
	double	len;

	len = vect_length(v);
	if (len == 0)
		return (v);
	return (vect_mult(v, 1 / len));
}

t_vector	two_points_vect(t_point a, t_point b)
{
	return (axes_sub(b, a));
}

t_vector	reflect_ray(t_vector ray, t_vector normal)
{
	return (axes_sub(ray, vect_mult(normal, 2 * dot_product(ray, normal))));
}

t_point	ray_point(t_point origin, t_vector direction, double t)
{
	return (axes_sum(origin, vect_mult(direction, t)));
}
