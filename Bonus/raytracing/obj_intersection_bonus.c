/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersection_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:10:25 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/25 21:34:17 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

bool	sphere_intersection(t_point origin, t_vector direction,
	t_object *sphere, double *t)
{
	t_vector	co;
	double		b;
	double		c;
	double		possible_t[2];

	if (sphere->type != sp)
		return (false);
	co = two_points_vect(sphere->pos, origin);
	b = 2 * dot_product(direction, co);
	c = vect_length2(co) - sphere->diameter * sphere->diameter / 4;
	if (!quadratic_equation(1, b, c, possible_t))
	{
		*t = 0;
		return (false);
	}
	if (possible_t[0] > PRECISION)
		*t = possible_t[0];
	else if (possible_t[1] > PRECISION)
		*t = possible_t[1];
	else
	{
		*t = 0;
		return (false);
	}
	return (true);
}

bool	plane_intersection(t_point origin, t_vector direction,
	t_object *plane, double *t)
{
	t_vector	p_o;
	double		d_dot_n;

	if (plane->type != pl)
		return (false);
	p_o = two_points_vect(plane->pos, origin);
	d_dot_n = dot_product(direction, plane->orientation);
	if (d_dot_n == 0)
	{
		*t = 0;
		return (false);
	}
	*t = -dot_product(p_o, plane->orientation) / d_dot_n;
	if (*t <= PRECISION)
		return (false);
	return (true);
}

double	get_lowest_t_tape(t_object *cylinder, t_vector co,
	t_vector direction, t_point origin)
{
	double		t;
	double		possible_t;
	t_vector	half_height_vect;
	t_point		c1;
	t_point		c2;

	half_height_vect = vect_mult(cylinder->orientation,
			cylinder->height / 2);
	c1 = axes_sum(cylinder->pos, half_height_vect);
	c2 = axes_sub(cylinder->pos, half_height_vect);
	t = 0;
	plane_intersection(origin, direction,
		&(t_object){pl, c1, cylinder->orientation, 0, 0, {0}, {0}, 0},
		&possible_t);
	if (is_tape_t(possible_t, cylinder, co, direction))
		t = possible_t;
	plane_intersection(origin, direction,
		&(t_object){pl, c2, cylinder->orientation, 0, 0, {0}, {0}, 0},
		&possible_t);
	if (is_tape_t(possible_t, cylinder,
			vect_mult(co, -1), vect_mult(direction, -1))
		&& t_minor(possible_t, t))
		t = possible_t;
	return (t);
}

double	get_lowest_t_body(t_object *cylinder, t_vector co,
	t_vector direction)
{
	double		t;
	double		abc[3];
	double		possible_t[2];
	t_vector	normal_ray;
	t_vector	normal_center;

	normal_ray = axes_sub(direction, vect_mult(cylinder->orientation,
				dot_product(direction, cylinder->orientation)));
	normal_center = axes_sub(co, vect_mult(cylinder->orientation,
				dot_product(co, cylinder->orientation)));
	abc[0] = vect_length2(normal_ray);
	abc[1] = 2 * dot_product(normal_ray, normal_center);
	abc[2] = vect_length2(normal_center)
		- cylinder->diameter * cylinder->diameter / 4;
	t = 0;
	if (quadratic_equation(abc[0], abc[1], abc[2], possible_t))
	{
		if (is_body_t(possible_t[0], cylinder, co, direction))
			t = possible_t[0];
		if (is_body_t(possible_t[1], cylinder, co, direction)
			&& t_minor(possible_t[1], t))
			t = possible_t[1];
	}
	return (t);
}

bool	cylinder_intersection(t_point origin, t_vector direction,
	t_object *cylinder, double *t)
{
	t_vector	co;
	double		possible_t;

	if (cylinder->type != cy)
		return (false);
	co = two_points_vect(cylinder->pos, origin);
	*t = get_lowest_t_body(cylinder, co, direction);
	possible_t = get_lowest_t_tape(cylinder, co, direction, origin);
	if (possible_t > PRECISION && t_minor(possible_t, *t))
		*t = possible_t;
	return (*t > PRECISION);
}
