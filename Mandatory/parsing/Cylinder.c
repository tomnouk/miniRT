/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:13:07 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 01:08:11 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	assign_position_cylinder(char *line, t_elem *elem, int *status)
{
	char	**split_position;

	split_position = ft_split(line, ',');
	if (ft_split_len(split_position) != 3)
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_POSITION);
		ft_free_split(split_position);
		return (true);
	}
	elem->pos.x = ft_atof(split_position[0]);
	elem->pos.y = ft_atof(split_position[1]);
	elem->pos.z = ft_atof(split_position[2]);
	ft_free_split(split_position);
	return (false);
}

bool	assign_orientation_cylinder(char *line, t_elem *elem, int *status)
{
	char	**split_orientation;

	split_orientation = ft_split(line, ',');
	if (ft_split_len(split_orientation) != 3)
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_ORIENTATION);
		ft_free_split(split_orientation);
		return (true);
	}
	elem->orientation.x = ft_atof(split_orientation[0]);
	elem->orientation.y = ft_atof(split_orientation[1]);
	elem->orientation.z = ft_atof(split_orientation[2]);
	ft_free_split(split_orientation);
	if (elem->orientation.x < -1 || elem->orientation.x > 1
		|| elem->orientation.y < -1 || elem->orientation.y > 1
		|| elem->orientation.z < -1 || elem->orientation.z > 1)
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_ORIENTATION);
		return (true);
	}
	return (false);
}

static bool	assign_diameter_hight(char **l_split, t_elem *elem, int *status)
{
	elem->diameter = ft_atof(l_split[3]);
	if (elem->diameter <= 0 || isnan(elem->diameter))
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_DIAMETER);
		return (true);
	}
	elem->height = ft_atof(l_split[4]);
	if (elem->height <= 0 || isnan(elem->height))
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_HIGHT);
		return (true);
	}
	return (false);
}

static void	assign_color_cylinder(char *line, t_elem *elem, int *status)
{
	char	**split_color;

	split_color = ft_split(line, ',');
	if (ft_split_len(split_color) != 3)
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_COLOR);
		ft_free_split(split_color);
		return ;
	}
	if (validate_color_values(split_color, status, 4))
		return ;
	elem->color.r = ft_atoi(split_color[0]);
	elem->color.g = ft_atoi(split_color[1]);
	elem->color.b = ft_atoi(split_color[2]);
	ft_free_split(split_color);
	if (elem->color.r < 0 || elem->color.r > 255 || elem->color.g < 0
		|| elem->color.g > 255 || elem->color.b < 0 || elem->color.b > 255)
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER_COLOR);
	}
}

void	check_assign_cylinder(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 6 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_CYLINDER);
		return ;
	}
	if (assign_position_cylinder(l_split[1], elem, status))
		return ;
	if (assign_orientation_cylinder(l_split[2], elem, status))
		return ;
	if (assign_diameter_hight(l_split, elem, status))
		return ;
	assign_color_cylinder(l_split[5], elem, status);
}
