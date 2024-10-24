/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperbolic_paraboloid_intersection_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:41:39 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/10/24 13:04:49 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static double	*calculate_abc_h_p(t_object *h_paraboloid, t_vector direction,
	t_point origin)
{
	double	*abc;

	abc = malloc(sizeof(double) * 3);
	abc[0] = h_paraboloid->h_p_abcdefg[pA] * direction.x * direction.x
		+ h_paraboloid->h_p_abcdefg[pB] * direction.y * direction.y
		+ h_paraboloid->h_p_abcdefg[pC] * direction.x * direction.y;
	abc[1] = 2 * (h_paraboloid->h_p_abcdefg[pA] * origin.x * direction.x
			+ h_paraboloid->h_p_abcdefg[pB] * origin.y * direction.y)
		+ h_paraboloid->h_p_abcdefg[pD] * direction.z
		+ h_paraboloid->h_p_abcdefg[pC] * (origin.x * direction.y
			+ origin.y * direction.x)
		+ h_paraboloid->h_p_abcdefg[pE] * direction.x
		+ h_paraboloid->h_p_abcdefg[pF] * direction.y;
	abc[2] = origin.x * origin.x * h_paraboloid->h_p_abcdefg[pA]
		+ origin.y * origin.y * h_paraboloid->h_p_abcdefg[pB]
		+ h_paraboloid->h_p_abcdefg[pD] * origin.z
		+ h_paraboloid->h_p_abcdefg[pC] * origin.x * origin.y
		+ h_paraboloid->h_p_abcdefg[pE] * origin.x
		+ h_paraboloid->h_p_abcdefg[pF] * origin.y
		+ h_paraboloid->h_p_abcdefg[pG];
	return (abc);
}

static t_point	get_h_p_vertex(double h_p_abcdefg[7])
{
	t_point	vertex;

	if (h_p_abcdefg[pA] == 0)
		pa_is_zero(h_p_abcdefg, &vertex);
	else if (4 * h_p_abcdefg[pA] * h_p_abcdefg[pB]
		- h_p_abcdefg[pD] * h_p_abcdefg[pD] == 0)
	{
		vertex.x = h_p_abcdefg[pE] / (2 * h_p_abcdefg[pA]);
		vertex.y = 0;
	}
	else
		nothing_is_zero(h_p_abcdefg, &vertex);
	if (h_p_abcdefg[pC] == 0)
		vertex.z = 0;
	else
		c_is_not_zero(h_p_abcdefg, &vertex);
	return (vertex);
}

static bool	is_in_h_p_diameter(t_point origin, t_vector direction,
	t_object *h_paraboloid, double t)
{
	double	distance;

	distance = vect_length2(axes_sub(ray_point(origin, direction, t),
				get_h_p_vertex(h_paraboloid->h_p_abcdefg)));
	return (distance < h_paraboloid->diameter * h_paraboloid->diameter / 4);
}

bool	hy_parab_intersection(t_point origin, t_vector direction,
	t_object *h_paraboloid, double *t)
{
	double	possible_t[2];
	double	*abc;

	if (h_paraboloid->type != h_p)
		return (false);
	abc = calculate_abc_h_p(h_paraboloid, direction, origin);
	if (!quadratic_equation(abc[0], abc[1], abc[2], possible_t))
	{
		free(abc);
		*t = 0;
		return (false);
	}
	free(abc);
	if (possible_t[0] > PRECISION && is_in_h_p_diameter(origin, direction,
			h_paraboloid, possible_t[0]))
		*t = possible_t[0];
	else if (possible_t[1] > PRECISION && is_in_h_p_diameter(origin, direction,
			h_paraboloid, possible_t[1]))
		*t = possible_t[1];
	else
	{
		*t = 0;
		return (false);
	}
	return (true);
}
