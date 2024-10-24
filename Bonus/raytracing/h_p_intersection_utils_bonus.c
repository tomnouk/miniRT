/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_p_intersection_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:00:22 by sdell-er          #+#    #+#             */
/*   Updated: 2024/10/24 13:07:34 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	pa_is_zero(double h_p_abcdefg[7], t_point *vertex)
{
	if (h_p_abcdefg[pD] == 0)
	{
		if (h_p_abcdefg[pB] == 0)
		{
			vertex->x = 0;
			vertex->y = 0;
		}
		else
		{
			vertex->x = 0;
			vertex->y = -h_p_abcdefg[pF] / (2 * h_p_abcdefg[pB]);
		}
	}
	else
	{
		vertex->x = 2 * h_p_abcdefg[pB] * h_p_abcdefg[pE]
			/ ((h_p_abcdefg[pD] * h_p_abcdefg[pD])
				- h_p_abcdefg[pF] / h_p_abcdefg[pD]);
		vertex->y = -h_p_abcdefg[pE] / h_p_abcdefg[pD];
	}
}

void	nothing_is_zero(double h_p_abcdefg[7], t_point *vertex)
{
	vertex->x = (h_p_abcdefg[pD] * h_p_abcdefg[pF]
			- 2 * h_p_abcdefg[pE] * h_p_abcdefg[pB])
		/ (4 * h_p_abcdefg[pA] * h_p_abcdefg[pB]
			- h_p_abcdefg[pD] * h_p_abcdefg[pD]);
	vertex->y = (h_p_abcdefg[pD] * h_p_abcdefg[pE]
			- 2 * h_p_abcdefg[pF] * h_p_abcdefg[pA])
		/ (4 * h_p_abcdefg[pA] * h_p_abcdefg[pB]
			- h_p_abcdefg[pD] * h_p_abcdefg[pD]);
}

void	c_is_not_zero(double h_p_abcdefg[7], t_point *vertex)
{
	vertex->z = (-1 / h_p_abcdefg[pC])
		* (h_p_abcdefg[pA] * vertex->x * vertex->x
			+ h_p_abcdefg[pB] * vertex->y * vertex->y
			+ h_p_abcdefg[pD] * vertex->x * vertex->y
			+ h_p_abcdefg[pE] * vertex->x
			+ h_p_abcdefg[pF] * vertex->y
			+ h_p_abcdefg[pG]);
}
