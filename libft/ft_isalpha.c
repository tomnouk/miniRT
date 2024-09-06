/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:05:09 by rpaic             #+#    #+#             */
/*   Updated: 2024/09/06 15:18:57 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include "libft.h"

int	ft_isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (2);
	return (0);
}

/*int main(void)
{
	printf("a->%d\n", isalpha('a')); 97
	printf("A->%d\n", isalpha('A')); 65
	printf("8->%d\n", isalpha('8'));
	printf("B->%d\n", isalpha('B'));
	
	printf("f_a->%d\n", ft_isalpha('a'));
	printf("f_A->%d\n", ft_isalpha('A'));
	printf("f_8->%d\n", ft_isalpha('8'));
	printf("f_B->%d\n", ft_isalpha('B'));
	
	//printf("ù->%d\n", isalpha('ù'));
}*/
