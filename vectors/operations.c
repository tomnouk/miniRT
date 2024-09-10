/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:50:54 by sdell-er          #+#    #+#             */
/*   Updated: 2024/09/10 17:12:32 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_vector	sum(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	sub(t_vector a, t_vector b)
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
	return (acos((vect_length2(a) * vect_length2(b) - vect_length2(sub(a, b)))
			/ (2 * vect_length(a) * vect_length(b))));
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

t_vector	mult(t_vector v, double a)
{
	t_vector	res;

	res.x = v.x * a;
	res.y = v.y * a;
	res.z = v.z * a;
	return (res);
}

t_vector	normalize(t_vector v)
{
	double		len;
	t_vector	res;

	len = vect_length(v);
	res.x = v.x / len;
	res.y = v.y / len;
	res.z = v.z / len;
	return (res);
}

t_vector	two_points_vect(t_point a, t_point b)
{
	t_vector	res;

	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return (res);
}

t_vector	reflect_ray(t_vector ray, t_vector normal)
{
	t_vector	res;
	double		dot;

	dot = dot_product(ray, normal);
	res.x = ray.x - 2 * dot * normal.x;
	res.y = ray.y - 2 * dot * normal.y;
	res.z = ray.z - 2 * dot * normal.z;
	return (res);
}
