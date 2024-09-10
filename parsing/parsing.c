/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:15:18 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 14:37:38 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static void check_and_open_file(char *file, int argc)
{
	int fd;
	char *p;
	
	p = NULL;
	fd = 0;
	if (file)
		p = ft_strrchr(file, '.');
	if (argc != 2 || !file || *file == '\0' || !p || ft_strncmp(p, ".rt", 3))
	{
		printf("%s", ERROR_ARGS);
		exit (1);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("%s", ERROR_FILE);
		perror(file);
		exit(1);
	}
	close(fd);
}

static void allocate_elem_initialize(t_elem **elem, char *file)
{
	int fd;
	int num_of_elem;
	int i;
	
	fd = open(file, O_RDONLY);
	i = -1;
	num_of_elem = get_num_of_elem(fd);
	if (num_of_elem == 0)
	{
		printf("%s", ERROR_EMPTY_FILE);
		exit(1);
	}
	*elem = malloc(sizeof(t_elem) * (num_of_elem + 1));
	while (++i < num_of_elem)
		ft_bzero(&(*elem)[i], sizeof(t_elem));
	(*elem)[num_of_elem].type = NONE;
	close(fd);
}

void parsing(t_elem *elem, char *file, int argc)
{
	check_and_open_file(file, argc);
	allocate_elem_initialize(&elem, file);
	read_check_assign(elem, file);
}