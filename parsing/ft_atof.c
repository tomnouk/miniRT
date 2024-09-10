/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:40:11 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 17:29:36 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// int	ft_isdigit(int c)
// {
// 	if (c > 47 && c < 58)
// 		return (1);
// 	return (0);
// }

static void assigning(double *result, double *fraction, double *divisor, bool *negative)
{
    *result = 0.0;
    *fraction = 0.0;
    *divisor = 10.0;
    *negative = false;
}

static void handle_sign(char **str, bool *negative, bool *fract)
{
	*fract = false;
    if (**str == '-' || **str == '+')
    {
        if (**str == '-')
            *negative = true;
        (*str)++;
    }
}

static double return_result(double result, double fraction, bool negative)
{
	if (negative)
		return (-result - fraction);
	return (result + fraction);
}

double ft_atof(char *str)
{
	double result;
	double fraction;
	double divisor;
	bool negative;
	bool fract;
	bool dot;

	assigning(&result, &fraction, &divisor, &negative);
	handle_sign(&str, &negative, &fract);
	dot = false;
	while (*str && (ft_isdigit(*str) || (*str == '.' && !dot)))
	{
		if (*str == '.')
			dot = true;
		if (*str == '.')
			fract = true;
		while (*str == '.')
			str++;
		if (fract)
			fraction += (*str - '0') / divisor;
		if (fract)
			divisor *= 10;
		else
			result = result * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return NAN;
	return (return_result(result, fraction, negative));
}

// int main()
// {
// 	char *str = "0.456";
// 	printf("%f\n", ft_atof(str));
// 	return 0;
// }
