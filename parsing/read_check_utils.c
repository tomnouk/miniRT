/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:06:45 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 13:19:24 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void remove_next_line(char *line)
{
	char *next_line;

	next_line = NULL;
	if (!line || !line[0])
		return ;
	next_line = ft_strrchr(line, '\n');
	if (next_line)
		*next_line = '\0';
}

void ft_free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

bool check_status(int *status, char **l_split)
{
    if (*status)
    {
        ft_free_split(l_split);
        printf("%s", ERROR_TYPE);
		return (true);
    }
	return (false);
}
