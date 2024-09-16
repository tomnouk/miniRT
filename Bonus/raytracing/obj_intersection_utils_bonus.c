/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:12:53 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

bool	quadratic_equation(double a, double b, double c, double t[2])
{
	double	delta;
	double	delta_sqrt;

	delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		t[0] = 0;
		t[1] = 0;
		return (false);
	}
	delta_sqrt = sqrt(delta);
	t[0] = (-b - delta_sqrt) / (2 * a);
	t[1] = (-b + delta_sqrt) / (2 * a);
	return (true);
}

bool	is_tape_t(double possible_t, t_object *cylinder, t_vector co,
	t_vector direction)
{
	if (possible_t > PRECISION
		&& vect_length(axes_sub(ray_point(co, direction, possible_t),
				vect_mult(cylinder->orientation, cylinder->height / 2)))
		<= cylinder->diameter / 2)
		return (true);
	return (false);
}

bool	is_body_t(double possible_t, t_object *cylinder, t_vector co,
	t_vector direction)
{
	if (possible_t > PRECISION
		&& ft_abs(dot_product(ray_point(co, direction, possible_t),
				cylinder->orientation)) <= cylinder->height / 2)
		return (true);
	return (false);
}

bool	t_minor(double t, double t_min)
{
	if (t < t_min || t_min <= PRECISION)
	{
		t_min = t;
		return (true);
	}
	return (false);
}
