/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:05:05 by aeid              #+#    #+#             */
/*   Updated: 2024/09/21 00:03:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	assign_position_light(char *line, t_elem *elem, int *status)
{
	char	**split_position;

	split_position = ft_split(line, ',');
	if (ft_split_len(split_position) != 3)
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_POSITION);
		ft_free_split(split_position);
		return (true);
	}
	elem->pos.x = ft_atof(split_position[0]);
	elem->pos.y = ft_atof(split_position[1]);
	elem->pos.z = ft_atof(split_position[2]);
	ft_free_split(split_position);
	return (false);
}

static void	assign_color_light(t_elem *elem)
{
	elem->color.r = 255;
	elem->color.g = 255;
	elem->color.b = 255;
}

void	check_assign_light(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 3 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_LIGHT);
		return ;
	}
	if (assign_position_light(l_split[1], elem, status))
		return ;
	elem->ratio = ft_atof(l_split[2]);
	if (elem->ratio < 0 || elem->ratio > 1 || isnan(elem->ratio))
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_RATIO);
		return ;
	}
	assign_color_light(elem);
}
