/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:50:24 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 01:08:11 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	assign_position_camera(char *line, t_elem *elem, int *status)
{
	char	**split_position;

	split_position = ft_split(line, ',');
	if (ft_split_len(split_position) != 3)
	{
		(*status)++;
		printf("%s", ERROR_CAMERA_POSITION);
		ft_free_split(split_position);
		return (true);
	}
	elem->pos.x = ft_atof(split_position[0]);
	elem->pos.y = ft_atof(split_position[1]);
	elem->pos.z = ft_atof(split_position[2]);
	ft_free_split(split_position);
	return (false);
}

static bool	assign_orientation_camera(char *line, t_elem *elem, int *status)
{
	char	**split_orientation;

	split_orientation = ft_split(line, ',');
	if (ft_split_len(split_orientation) != 3)
	{
		(*status)++;
		printf("%s", ERROR_CAMERA_ORIENTATION);
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
		printf("%s", ERROR_CAMERA_ORIENTATION);
		return (true);
	}
	return (false);
}

static void	assign_fov(char *line, t_elem *elem, int *status)
{
	elem->fov = ft_atoi(line);
	if (elem->fov < 0 || elem->fov > 180)
	{
		(*status)++;
		printf("%s", ERROR_CAMERA_FOV);
	}
}

void	check_assign_camera(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 4 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_CAMERA);
		return ;
	}
	if (assign_position_camera(l_split[1], elem, status))
		return ;
	if (assign_orientation_camera(l_split[2], elem, status))
		return ;
	assign_fov(l_split[3], elem, status);
}
