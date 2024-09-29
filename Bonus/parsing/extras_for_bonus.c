/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras_for_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:37:20 by aeid              #+#    #+#             */
/*   Updated: 2024/09/29 21:14:08 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	assigning_if_one_char(char *string, int *status, t_elem *elem)
{
	if (!ft_strncmp(string, "A", 1))
		elem->type = A;
	else if (!ft_strncmp(string, "C", 1))
		elem->type = C;
	else if (!ft_strncmp(string, "L", 1))
		elem->type = L;
	else
		(*status)++;
}

void	assigning_if_more_chars(char *string, int *status, t_elem *elem)
{
	if (!ft_strncmp(string, "pl", 2))
		elem->type = pl;
	else if (!ft_strncmp(string, "sp", 2))
		elem->type = sp;
	else if (!ft_strncmp(string, "cy", 2))
		elem->type = cy;
	else if (!ft_strncmp(string, "h_p", 3))
		elem->type = h_p;
	else
		(*status)++;
}
