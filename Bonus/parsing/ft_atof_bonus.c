/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:40:11 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static void	assigning(double *result, double *fraction, double *divisor,
		bool *negative)
{
	*result = 0.0;
	*fraction = 0.0;
	*divisor = 10.0;
	*negative = false;
}

static void	handle_sign(char **str, bool *negative, bool *dot)
{
	*dot = false;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*negative = true;
		(*str)++;
	}
}

static double	return_result(double result, double fraction, bool negative)
{
	if (negative)
		return (-result - fraction);
	return (result + fraction);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	bool	negative;
	bool	dot;

	assigning(&result, &fraction, &divisor, &negative);
	handle_sign(&str, &negative, &dot);
	while (*str && (ft_isdigit(*str) || (*str == '.' && !dot)))
	{
		if (*str == '.')
			dot = true;
		while (*str == '.')
			str++;
		if (dot)
			fraction += (*str - '0') / divisor;
		if (dot)
			divisor *= 10;
		else
			result = result * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (NAN);
	return (return_result(result, fraction, negative));
}
