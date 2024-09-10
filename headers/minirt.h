/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:44 by aeid              #+#    #+#             */
/*   Updated: 2024/09/10 19:46:54 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

# include "../libft/libft.h"
# include "get_next_line.h"

# define ERROR_ARGS "Error\nInvalid arguments\n"
# define ERROR_FILE "Error\n"
# define ERROR_EMPTY_FILE "Error\nEmpty file\n"
# define ERROR_MAP "Error\nInvalid map\n"
# define ERROR_TYPE "Error\nInvalid type\n"
# define ERROR_AMBIENT "Error\nInvalid ambient\n"
# define ERROR_AMBIENT_RATIO "Error\nInvalid ambient ratio\n"
# define ERROR_AMBIENT_COLOR "Error\nInvalid ambient color\n"
# define ER_AMBIENT_COLOR_VALUE "Error\nInvalid ambient color value\n"
# define ERROR_CAMERA "Error\nInvalid camera\n"
# define ERROR_CAMERA_POSITION "Error\nInvalid camera position\n"
# define ERROR_CAMERA_FOV "Error\nInvalid camera fov\n"
# define ERROR_CAMERA_ORIENTATION "Error\nInvalid camera orientation\n"
# define ERROR_LIGHT "Error\nInvalid light\n"
# define ERROR_LIGHT_POSITION "Error\nInvalid light position\n"
# define ERROR_LIGHT_RATIO "Error\nInvalid light ratio\n"
# define ERROR_LIGHT_COLOR "Error\nInvalid light color\n"
# define ER_LIGHT_COLOR_VALUE "Error\nInvalid light color value\n"
# define ERROR_REPITITION "Error\nRepitition of element\n"

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

typedef t_axes t_vector;
typedef t_axes t_point;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_elem
{
	t_type	type;
	t_point	pos; //cooredinates x, y, z
	t_vector	orientation; //vector x, y, z
	t_color	color;
	int		fov; //from 0 to 180
	double	ratio; //should be between 0 and 1
	double	diameter;
	double	height;
}			t_elem;

void parsing(t_elem *elem, char *file, int argc);
void read_check_assign(t_elem *elem, char *file, int *status);
int get_num_of_elem(int fd);
bool check_empty_line(char *line);
void ft_free_split(char **split);
void remove_next_line(char *line);
double ft_atof(char *str);
bool check_status(int *status, char **l_split);
void check_assign_ambient(char **l_split, t_elem *elem, int *status);
int ft_split_len(char **split);
bool check_digits(char **l_split);
int check_digits_advanced(char *str);
void check_assign_camera(char **l_split, t_elem *elem, int *status);
void check_assign_light(char **l_split, t_elem *elem, int *status);
int validate_color_values(char **split_color, int *status, int type);
void check_repitition(t_elem *elem, int *status);

#endif


