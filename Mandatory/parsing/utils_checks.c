/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 01:08:11 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_split_len(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

static int	ft_isdigit_advanced(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '.' || c == '-' || c == '+' || c == ',')
		return (2);
	return (0);
}

bool	check_digits(char **l_split)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (l_split[j])
	{
		while (l_split[j][i])
		{
			if (!ft_isdigit_advanced(l_split[j][i]))
				return (true);
			i++;
		}
		i = 0;
		j++;
	}
	return (false);
}

int	check_digits_advanced(char *str)
{
	int	i;
	int	output;

	i = 0;
	output = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		output = ft_isdigit_advanced(str[i]);
		if (output == 2)
			return (1);
		i++;
	}
	return (0);
}

int	validate_color_values(char **split_color, int *status, int type)
{
	int	i;

	i = -1;
	while (split_color[++i])
	{
		if (check_digits_advanced(split_color[i] + 1))
		{
			(*status)++;
			if (type == 0)
				printf("%s", ER_AMBIENT_COLOR_VALUE);
			if (type == 1)
				printf("%s", ER_LIGHT_COLOR_VALUE);
			if (type == 2)
				printf("%s", ER_SPHERE_COLOR_VALUE);
			if (type == 3)
				printf("%s", ER_PLANE_COLOR_VALUE);
			if (type == 4)
				printf("%s", ER_CYLINDER_COLOR_VALUE);
			ft_free_split(split_color);
			return (1);
		}
	}
	return (0);
}
