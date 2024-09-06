/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:00:52 by aeid              #+#    #+#             */
/*   Updated: 2024/09/06 17:04:52 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"


static void check_first_char(char *string, int *status, t_elem *elem)
{
	int type;
	
	type = ft_isalpha(string[0]);
	if (ft_strlen(string) > 2)
		(*status)++;
	if (type == 1)
	{
		if (!ft_strncmp(string, "A", 1))
			elem->type = A;
		else if (!ft_strncmp(string, "C", 1))
			elem->type = C;
		else if (!ft_strncmp(string, "L", 1))
			elem->type = L;
	}
	else if (type == 2)
	{
		if (!ft_strncmp(string, "pl", 2))
			elem->type = pl;
		else if (!ft_strncmp(string, "sp", 2))
			elem->type = sp;
		else if (!ft_strncmp(string, "cy", 2))
			elem->type = cy;
	}
	else
		(*status)++;
}

static void remove_next_line(char *line)
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

void check_status(int *status, char **l_split, char *line)
{
    if (*status)
    {
        ft_free_split(l_split);
        free(line);
		//edit the error message
        printf("%s", "ERROR_TYPE");
    }
	return ;
}

/// debug
void print_matrix(char **l_split)
{
	int i;

	i = -1;
	while (l_split[++i])
		printf("%s\n", l_split[i]);
}

static void check_assign(char *line, int *status, t_elem *elem)
{
	char **l_split;

	l_split = NULL;
	remove_next_line(line);
	l_split = ft_split(line, ' ');
	print_matrix(l_split);
	check_first_char(l_split[0], status, elem);
	check_status(status, l_split, line);
	if (*status)
		return ;
}

void read_check_assign(t_elem *elem, char *file)
{
	int fd;
	char *line;
	int status;
	int i;

	fd = open(file, O_RDONLY);
	status = 0;
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (check_empty_line(line))
			check_assign(line, &status, &elem[++i]);
		if (status)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (status)
	{
		get_next_line(-1);
		free(elem);
		close(fd);
		exit(1);
	}
}
