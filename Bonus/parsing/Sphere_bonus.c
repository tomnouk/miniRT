/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:32:12 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static bool	assign_position_sphere(char *line, t_elem *elem, int *status)
{
	char	**split_position;

	split_position = ft_split(line, ',');
	if (ft_split_len(split_position) != 3)
	{
		(*status)++;
		printf("%s", ERROR_SPHERE_POSITION);
		ft_free_split(split_position);
		return (true);
	}
	elem->pos.x = ft_atof(split_position[0]);
	elem->pos.y = ft_atof(split_position[1]);
	elem->pos.z = ft_atof(split_position[2]);
	ft_free_split(split_position);
	return (false);
}

static void	assign_color_sphere(char *line, t_elem *elem, int *status)
{
	char	**split_color;

	split_color = ft_split(line, ',');
	if (ft_split_len(split_color) != 3)
	{
		(*status)++;
		printf("%s", ERROR_SPHERE_COLOR);
		ft_free_split(split_color);
		return ;
	}
	if (validate_color_values(split_color, status, 2))
		return ;
	elem->color.r = ft_atoi(split_color[0]);
	elem->color.g = ft_atoi(split_color[1]);
	elem->color.b = ft_atoi(split_color[2]);
	ft_free_split(split_color);
	if (elem->color.r < 0 || elem->color.r > 255 || elem->color.g < 0
		|| elem->color.g > 255 || elem->color.b < 0 || elem->color.b > 255)
	{
		(*status)++;
		printf("%s", ERROR_SPHERE_COLOR);
	}
}

void	check_assign_sphere(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 4 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_SPHERE);
		return ;
	}
	if (assign_position_sphere(l_split[1], elem, status))
		return ;
	elem->diameter = ft_atof(l_split[2]);
	if (elem->diameter <= 0 || isnan(elem->diameter))
	{
		(*status)++;
		printf("%s", ERROR_SPHERE_DIAMETER);
		return ;
	}
	assign_color_sphere(l_split[3], elem, status);
}
