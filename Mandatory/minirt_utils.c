/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:19:16 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/16 01:08:58 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	before_digit(char *nptr, int *n, int *i)
{
	while ((nptr[*n] >= 9 && nptr[*n] <= 13) || nptr[*n] == ' ')
		*n += 1;
	if (nptr[*n] == '-' || nptr[*n] == '+')
	{
		if (nptr[*n] == '-')
			*i *= -1;
		*n += 1;
	}
}

double	my_ft_atof(char *nptr)
{
	int		i;
	int		n;
	int		dot;
	double	res;

	n = 0;
	i = 1;
	res = 0;
	before_digit(nptr, &n, &i);
	dot = 0;
	while ((nptr[n] >= '0' && nptr[n] <= '9') || nptr[n] == '.')
	{
		if (nptr[n] == '.')
			dot = 1;
		else if (!dot)
			res = res * 10 + (nptr[n] - '0');
		else
		{
			res += (nptr[n] - '0') / pow(10, dot);
			dot++;
		}
		n++;
	}
	return (res * i);
}

t_elem	find_elem(t_elem *elem, t_type type)
{
	while (elem->type != NONE)
	{
		if (elem->type == type)
			return (*elem);
		elem++;
	}
	return (*elem);
}

void	display_value(t_data *data, double value, char *label, int y_offset)
{
	char	*str;

	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, y_offset, 0x00FFFFFF, label);
	str = ft_ftoa(value);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		180, y_offset, 0x00FFFFFF, str);
	free(str);
}

void	display_axes(t_data *data, t_axes axes, char *label, int y_offset)
{
	char	*str;

	display_value(data, axes.x, label, y_offset);
	str = ft_ftoa(axes.y);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		280, y_offset, 0x00FFFFFF, str);
	free(str);
	str = ft_ftoa(axes.z);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		380, y_offset, 0x00FFFFFF, str);
	free(str);
}
