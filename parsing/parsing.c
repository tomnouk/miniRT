/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:15:18 by aeid              #+#    #+#             */
/*   Updated: 2024/09/04 19:31:59 by aeid             ###   ########.fr       */
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

void parsing(t_elem *elem, char *file, int argc)
{
	check_and_open_file(file, argc);
	elem = malloc(sizeof(t_elem));
	ft_bzero(elem, sizeof(t_elem));
	read_check_assign(elem, file);
}