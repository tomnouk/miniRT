/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_properties_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:41:37 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

double	vect_length2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vect_length(t_vector v)
{
	return (sqrt(vect_length2(v)));
}

t_vector	normalize(t_vector v)
{
	double	len;

	len = vect_length(v);
	if (len == 0)
		return (v);
	return (vect_mult(v, 1 / len));
}
