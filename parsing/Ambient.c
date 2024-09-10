/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:14:05 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 14:51:10 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static void assign_color_ambient(char *line, t_elem *elem, int *status)
{
	char **split_color;
	// int i;

	split_color = ft_split(line, ',');
	if (ft_split_len(split_color) != 3)
	{
		(*status)++;
		printf("%s", ERROR_AMBIENT_COLOR);
		ft_free_split(split_color);
		return ;
	}
	// i = -1;
	// while (++i < 3)
	// {
	// 	if (ft_strchr(split_color[i] + 1, '-'))
	// 	{
	// 		(*status)++;
	// 		printf("%s", ERROR_AMBIENT_COLOR);
	// 		ft_free_split(split_color);
	// 		return ;
	// 	}
	// }
	elem->color.r = ft_atoi(split_color[0]);
	elem->color.g = ft_atoi(split_color[1]);
	elem->color.b = ft_atoi(split_color[2]);
	ft_free_split(split_color);
	if (elem->color.r < 0 || elem->color.r > 255 || elem->color.g < 0 || elem->color.g > 255 || elem->color.b < 0 || elem->color.b > 255)
	{
		(*status)++;
		printf("%s", ERROR_AMBIENT_COLOR);
	}
}

void check_assign_ambient(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 3 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_AMBIENT);
		return ;
	}
	elem->ratio = ft_atof(l_split[1]);
	//printf("%f\n", elem->ratio);
	if (elem->ratio < 0 || elem->ratio > 1 || isnan(elem->ratio))
	{
		(*status)++;
		printf("%s", ERROR_AMBIENT_RATIO);
		return ;
	}
	assign_color_ambient(l_split[2], elem, status);
	// printf("%d\n", elem->color.r);
	// printf("%d\n", elem->color.g);
	// printf("%d\n", elem->color.b);
}
