/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:26:14 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/18 10:35:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_vector	calculate_cylinder_normal(t_object *cylinder,
	t_vector direction, t_point origin)
{
	double		t_tape;
	double		t_body;
	t_vector	co;
	t_vector	dir_on_axis_proj;

	co = two_points_vect(cylinder->pos, origin);
	t_tape = get_lowest_t_tape(cylinder, co, direction, origin);
	t_body = get_lowest_t_body(cylinder, co, direction);
	if (t_tape > PRECISION && (t_tape < t_body || t_body <= PRECISION))
	{
		if (dot_product(direction, cylinder->orientation) > 0)
			return (cylinder->orientation);
		return (vect_mult(cylinder->orientation, -1));
	}
	dir_on_axis_proj = vect_mult(cylinder->orientation,
			dot_product(direction, cylinder->orientation));
	return (axes_sub(dir_on_axis_proj, direction));
}

static bool	hit_obj_before_light(t_data *data, t_point p, t_vector p_to_light)
{
	double	t_obj;

	if (first_obj_hit(data, p, p_to_light, &t_obj) != NULL
		&& t_obj < vect_length(two_points_vect(p, data->light.pos)))
		return (true);
	return (false);
}

double	light_intensity(t_data *data, t_vector direction, t_point p,
	t_object *obj)
{
	t_vector	normal;
	t_vector	p_to_light;
	double		intensity;

	if (obj->type == pl)
		normal = obj->orientation;
	else if (obj->type == sp)
		normal = normalize(two_points_vect(obj->pos, p));
	else if (obj->type == cy)
		normal = calculate_cylinder_normal(obj, direction, data->camera.pos);
	p_to_light = normalize(two_points_vect(p, data->light.pos));
	if (hit_obj_before_light(data, p, p_to_light))
		return (0);
	intensity = ft_abs(dot_product(normal, p_to_light));
	if (obj->shininess > 0)
	{
		intensity += pow(dot_product(direction,
					reflect_ray(p_to_light, normal)), obj->shininess);
		if (intensity < 0)
			intensity = 0;
	}
	return (intensity * data->light.ratio);
}
