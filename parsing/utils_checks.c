/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 13:57:00 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int ft_split_len(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

static bool ft_isdigit_advanced(char c)
{
	if ((c >= '0' && c <= '9') || c == '.' || c == '-' || c == '+' || c == ',')
		return (true);
	return (false);
}

bool check_digits(char **l_split)
{
	int i;
	int j;

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
