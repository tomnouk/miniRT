/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperbolic_paraboloid_intersection_bonus.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:41:39 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/25 21:41:40 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static double	calculate_a_h_p(t_object *h_paraboloid, t_vector direction)
{
	return (h_paraboloid->h_p_abcdefg[0] * direction.x * direction.x
		+ h_paraboloid->h_p_abcdefg[1] * direction.y * direction.y
		+ h_paraboloid->h_p_abcdefg[2] * direction.x * direction.y);
}

static double	calculate_b_h_p(t_object *h_paraboloid, t_vector direction,
	t_point origin)
{
	return (2 * (h_paraboloid->h_p_abcdefg[0] * origin.x * direction.x
			+ h_paraboloid->h_p_abcdefg[1] * origin.y * direction.y)
		+ h_paraboloid->h_p_abcdefg[3] * direction.z
		+ h_paraboloid->h_p_abcdefg[2] * (origin.x * direction.y
			+ origin.y * direction.x)
		+ h_paraboloid->h_p_abcdefg[4] * direction.x
		+ h_paraboloid->h_p_abcdefg[5] * direction.y);
}

static double	calculate_c_h_p(t_object *h_paraboloid, t_point origin)
{
	return (origin.x * origin.x * h_paraboloid->h_p_abcdefg[0]
		+ origin.y * origin.y * h_paraboloid->h_p_abcdefg[1]
		+ h_paraboloid->h_p_abcdefg[3] * origin.z
		+ h_paraboloid->h_p_abcdefg[2] * origin.x * origin.y
		+ h_paraboloid->h_p_abcdefg[4] * origin.x
		+ h_paraboloid->h_p_abcdefg[5] * origin.y
		+ h_paraboloid->h_p_abcdefg[6]);
}

bool	hy_parab_intersection(t_point origin, t_vector direction,
	t_object *h_paraboloid, double *t)
{
	double	possible_t[2];
	int		abc[3];

	if (h_paraboloid->type != h_p)
		return (false);
	abc[0] = calculate_a_h_p(h_paraboloid, direction);
	abc[1] = calculate_b_h_p(h_paraboloid, direction, origin);
	abc[2] = calculate_c_h_p(h_paraboloid, origin);
	if (!quadratic_equation(abc[0], abc[1], abc[2], possible_t))
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
