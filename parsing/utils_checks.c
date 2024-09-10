/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:56:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 17:55:58 by aeid             ###   ########.fr       */
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

static int ft_isdigit_advanced(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '.' || c == '-' || c == '+' || c == ',')
		return (2);
	return (0);
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

int check_digits_advanced(char *str)
{
	int i;
	int output;

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
