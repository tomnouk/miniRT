/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:08:18 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/14 17:10:00 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

double	ft_atof(char *nptr)
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
			res += (nptr[n] - '0') / ft_pow(10, dot);
			dot++;
		}
		n++;
	}
	return (res * i);
}
