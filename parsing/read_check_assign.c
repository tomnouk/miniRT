/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:00:52 by aeid              #+#    #+#             */
/*   Updated: 2024/09/05 20:44:48 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static void check_first_char(char *string, int *status)
{
	if (ft_strlen(string) > 2)
		*status++;
	//check and assign types
}

static char **check_line(char *line, int *status)
{
	char **l_split;

	l_split = ft_split(line, ' ');
	if (!l_split || !l_split[0])
	{
		//maybe free?
		return (NULL);
	}
	check_first_char(l_split[0], status);
}

static void remove_next_line(char *line)
{
	char *next_line;

	next_line = ft_strrchr(line, '\n');
	if (next_line)
		*next_line = '\0';
}

void read_check_assign(t_elem *elem, char *file)
{
	int fd;
	char *line;
	int status;
	char **l_split;

	fd = open(file, O_RDONLY);
	status = 0;
	l_split = NULL;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		remove_next_line(line);
		l_split = check_line(line, &status);
		if (l_split)
		{
			//assign values
		}
	}
	if (status)
	{
		printf("%s", ERROR_MAP);
		free_all(elem);
		exit(1);
	}
}
