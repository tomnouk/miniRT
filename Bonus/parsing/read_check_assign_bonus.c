/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_assign_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:00:52 by aeid              #+#    #+#             */
/*   Updated: 2024/09/16 17:51:42 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

static void	check_first_char(char *string, int *status, t_elem *elem)
{
	if (ft_strlen(string) == 1)
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
	else if (ft_strlen(string) == 2)
	{
		if (!ft_strncmp(string, "pl", 2))
			elem->type = pl;
		else if (!ft_strncmp(string, "sp", 2))
			elem->type = sp;
		else if (!ft_strncmp(string, "cy", 2))
			elem->type = cy;
		else
			(*status)++;
	}
	else
		(*status)++;
}

static void	distribution_assign(char **l_split, t_elem *elem, int *status)
{
	if (elem->type == A)
		check_assign_ambient(l_split, elem, status);
	else if (elem->type == C)
		check_assign_camera(l_split, elem, status);
	else if (elem->type == L)
		check_assign_light(l_split, elem, status);
	else if (elem->type == pl)
		check_assign_plane(l_split, elem, status);
	else if (elem->type == sp)
		check_assign_sphere(l_split, elem, status);
	else if (elem->type == cy)
		check_assign_cylinder(l_split, elem, status);
}

static void	check_assign(char *line, int *status, t_elem *elem)
{
	char	**l_split;

	l_split = NULL;
	remove_next_line(line);
	l_split = ft_split(line, ' ');
	check_first_char(l_split[0], status, elem);
	if (check_status(status, l_split))
		return ;
	distribution_assign(l_split, elem, status);
	ft_free_split(l_split);
}

void	read_check_assign(t_elem *elem, char *file, int *status)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	i = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (check_empty_line(line))
			check_assign(line, status, &elem[++i]);
		if (*status)
			break ;
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	if (!*status)
		check_repitition(elem, status);
	if (line != NULL)
		free(line);
	close(fd);
}
