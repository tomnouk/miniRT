/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_creation_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:47:35 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

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

t_vector	rotate_vector(t_vector v, t_vector direction)
{
	t_vector	axis;
	double		angle;
	double		cos_angle;
	double		sin_angle;
	t_vector	rotated;

	angle = acos(direction.z);
	axis = cross_product((t_vector){0, 0, 1}, direction);
	axis = normalize(axis);
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	rotated.x = (axis.x * axis.x + (1 - axis.x * axis.x) * cos_angle) * v.x
		+ ((1 - cos_angle) * axis.x * axis.y - sin_angle * axis.z) * v.y
		+ ((1 - cos_angle) * axis.x * axis.z + sin_angle * axis.y) * v.z;
	rotated.y = ((1 - cos_angle) * axis.x * axis.y + sin_angle * axis.z) * v.x
		+ (axis.y * axis.y + (1 - axis.y * axis.y) * cos_angle) * v.y
		+ ((1 - cos_angle) * axis.y * axis.z - sin_angle * axis.x) * v.z;
	rotated.z = ((1 - cos_angle) * axis.x * axis.z - sin_angle * axis.y) * v.x
		+ ((1 - cos_angle) * axis.y * axis.z + sin_angle * axis.x) * v.y
		+ (axis.z * axis.z + (1 - axis.z * axis.z) * cos_angle) * v.z;
	return (rotated);
}
