/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:44 by aeid              #+#    #+#             */
/*   Updated: 2024/09/06 16:01:09 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

# include "../libft/libft.h"
# include "get_next_line.h"

# define ERROR_ARGS "Error\nInvalid arguments"
# define ERROR_FILE "Error\n"
# define ERROR_MAP "Error\nInvalid map"
# define ERROR_TYPE "Error\nInvalid type"

typedef enum type
{
	NONE,
	A,
	C,
	L,
	pl,
	sp,
	cy,
}			t_type;

typedef struct s_axes
{
	double	x;
	double	y;
	double	z;
}			t_axes;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_elem
{
	t_type	type;
	t_axes	pos;
	t_axes	rot;
	t_axes	norm_vect;
	t_color	color;
	int		fov;
	double	ratio;
	double	diameter;
	double	height;
}			t_elem;

void parsing(t_elem *elem, char *file, int argc);
void read_check_assign(t_elem *elem, char *file);
int get_num_of_elem(int fd);
bool check_empty_line(char *line);
