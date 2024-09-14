/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:11:29 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/14 18:33:32 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ftoa(double n)
{
	double	fpart;
	int		i;
	char	*res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa((int)n);
	fpart = ft_abs(n - ft_atof(tmp1));
	i = 0;
	while (fpart - (int)fpart != 0 && i < 6)
	{
		fpart *= 10;
		i++;
	}
	tmp2 = ft_calloc(++i + 1, sizeof(char));
	if (!tmp2)
		return (NULL);
	while (i--)
	{
		tmp2[i] = (int)fpart % 10 + '0';
		fpart /= 10;
	}
	tmp2[0] = '.' * (n - (int)n != 0) + '\0' * (n - (int)n == 0);
	res = ft_strjoin(tmp1, tmp2);
	return (free(tmp1), free(tmp2), res);
}
