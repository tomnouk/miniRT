/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:47:26 by aeid              #+#    #+#             */
/*   Updated: 2024/09/29 21:14:37 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static bool	assign_first_seven_params(char *string, t_elem *elem, int *status)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(string, ',');
	if (ft_split_len(split) != 7)
	{
		(*status)++;
		printf("%s", ERROR_PARABOLOID_PARAMS);
		ft_free_split(split);
		return (true);
	}
	while (++i < 7)
	{
		elem->h_p_abcdefg[i] = ft_atof(split[i]);
		if (isnan(elem->h_p_abcdefg[i]))
		{
			(*status)++;
			printf("%s", ERROR_PARABOLOID_PARAMS);
			ft_free_split(split);
			return (true);
		}
	}
	ft_free_split(split);
	return (false);
}

static bool	assign_diameter_height_parab(char *string, t_elem *elem,
		int *status)
{
	elem->diameter = ft_atof(string);
	if (elem->diameter <= 0 || isnan(elem->diameter))
	{
		(*status)++;
		printf("%s", ERROR_PARABOLOID_DIAMETER);
		return (true);
	}
	return (false);
}

static void	assign_color_paraboloid(char *line, t_elem *elem, int *status)
{
	char	**split_color;

	split_color = ft_split(line, ',');
	if (ft_split_len(split_color) != 3)
	{
		(*status)++;
		printf("%s", ERROR_PARABOLOID_COLOR);
		ft_free_split(split_color);
		return ;
	}
	if (validate_color_values(split_color, status, 5))
		return ;
	elem->color.r = ft_atoi(split_color[0]);
	elem->color.g = ft_atoi(split_color[1]);
	elem->color.b = ft_atoi(split_color[2]);
	ft_free_split(split_color);
	if (elem->color.r < 0 || elem->color.r > 255 || elem->color.g < 0
		|| elem->color.g > 255 || elem->color.b < 0 || elem->color.b > 255)
	{
		(*status)++;
		printf("%s", ERROR_PARABOLOID_COLOR);
	}
}

void	check_assign_paraboloid(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 4 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_PARABOLOID);
		return ;
	}
	if (assign_first_seven_params(l_split[1], elem, status))
		return ;
	if (assign_diameter_height_parab(l_split[2], elem, status))
		return ;
	assign_color_paraboloid(l_split[3], elem, status);
}
