/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lighting_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:26:14 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/26 12:51:51 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

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
			return (normalize(cylinder->orientation));
		return (normalize(vect_mult(cylinder->orientation, -1)));
	}
	dir_on_axis_proj = vect_mult(cylinder->orientation,
			dot_product(direction, cylinder->orientation));
	return (normalize(axes_sub(dir_on_axis_proj, direction)));
}

static t_vector	calculate_h_p_normal(double h_p_abcdefg[7], t_point p)
{
	t_vector	normal;

	normal.x = 2 * h_p_abcdefg[pA] * p.x + h_p_abcdefg[pD] * p.y
		+ h_p_abcdefg[pE];
	normal.y = 2 * h_p_abcdefg[pB] * p.y + h_p_abcdefg[pD] * p.x
		+ h_p_abcdefg[pF];
	normal.z = h_p_abcdefg[pC];
	return (normalize(normal));
}

static bool	hit_obj_before_light(t_data *data, t_point p, t_vector p_to_light,
t_light *light)
{
	double	t_obj;

	if (first_obj_hit(data, p, p_to_light, &t_obj) != NULL
		&& t_obj < vect_length(two_points_vect(p, light->pos)))
		return (true);
	return (false);
}

static t_vector	get_obj_normal(t_object *obj, t_vector direction, t_point p,
	t_point camera_pos)
{
	if (obj->type == pl)
		return (obj->orientation);
	else if (obj->type == sp)
		return (normalize(two_points_vect(obj->pos, p)));
	else if (obj->type == cy)
		return (calculate_cylinder_normal(obj, direction, camera_pos));
	else if (obj->type == h_p)
		return (calculate_h_p_normal(obj->h_p_abcdefg, p));
	return ((t_vector){0, 0, 0});
}

t_color	total_light_color(t_data *data, t_vector direction, t_point p,
	t_object *obj)
{
	t_vector	normal;
	t_vector	p_to_light;
	t_color		color;
	double		intensity;
	int			i;

	normal = get_obj_normal(obj, direction, p, data->camera.pos);
	ft_bzero(&color, sizeof(t_color));
	i = -1;
	while (++i < data->num_of_lights)
	{
		p_to_light = normalize(two_points_vect(p, data->lights[i].pos));
		if (hit_obj_before_light(data, p, p_to_light, &data->lights[i]))
			continue ;
		intensity = ft_abs(dot_product(normal, p_to_light));
		if (obj->shininess > 0)
		{
			intensity += pow(dot_product(direction,
						reflect_ray(p_to_light, normal)), obj->shininess);
			intensity *= intensity > 0;
		}
		color = sum_colors(color, mult_color_ratio(data->lights[i].color,
					intensity * data->lights[i].ratio));
	}
	return (color);
}
