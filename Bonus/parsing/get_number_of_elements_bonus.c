/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number_of_elements_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:41:35 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static bool	ft_isspace(char c)
{
	if (c == '\0')
		return (false);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

bool	check_empty_line(char *line)
{
	int	i;

	i = -1;
	while (ft_isspace(line[++i]))
		;
	if (line[i] == '\0' || line[i] == '\n')
		return (false);
	return (true);
}

int	get_num_of_elem(int fd)
{
	int		num_of_elem;
	char	*line;

	num_of_elem = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (check_empty_line(line))
			num_of_elem++;
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	return (num_of_elem);
}
