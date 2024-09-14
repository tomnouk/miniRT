/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:44 by aeid              #+#    #+#             */
/*   Updated: 2024/09/14 13:27:14 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
# define ERROR_SPHERE "Error\nInvalid sphere\n"
# define ERROR_SPHERE_POSITION "Error\nInvalid sphere position\n"
# define ERROR_SPHERE_DIAMETER "Error\nInvalid sphere diameter\n"
# define ERROR_SPHERE_COLOR "Error\nInvalid sphere color\n"
# define ER_SPHERE_COLOR_VALUE "Error\nInvalid sphere color value\n"
# define ERROR_PLANE "Error\nInvalid plane\n"
# define ERROR_PLANE_POSITION "Error\nInvalid plane position\n"
# define ERROR_PLANE_ORIENTATION "Error\nInvalid plane orientation\n"
# define ERROR_PLANE_COLOR "Error\nInvalid plane color\n"
# define ER_PLANE_COLOR_VALUE "Error\nInvalid plane color value\n"
# define ERROR_CYLINDER "Error\nInvalid cylinder\n"
# define ERROR_CYLINDER_POSITION "Error\nInvalid cylinder position\n"
# define ERROR_CYLINDER_ORIENTATION "Error\nInvalid cylinder orientation\n"
# define ERROR_CYLINDER_DIAMETER "Error\nInvalid cylinder diameter\n"
# define ERROR_CYLINDER_HIGHT "Error\nInvalid cylinder hight\n"
# define ERROR_CYLINDER_COLOR "Error\nInvalid cylinder color\n"
# define ER_CYLINDER_COLOR_VALUE "Error\nInvalid cylinder color value\n"

# define WIDTH 1080
# define HEIGHT 720
# define BACKGROUND_R 255
# define BACKGROUND_G 255
# define BACKGROUND_B 255

typedef enum type
{
	NONE,
	A,
	C,
	L,
	pl,
	sp,
	cy,
}				t_type;

typedef struct s_axes
{
	double		x;
	double		y;
	double		z;
}				t_axes;

typedef t_axes	t_vector;
typedef t_axes	t_point;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_elem
{
	t_type		type;
	t_point		pos;
	t_vector	orientation;
	t_color		color;
	double		fov;
	double		ratio;
	double		diameter;
	double		height;
	double		shininess;
}				t_elem;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_minilibx
{
	void		*mlx;
	void		*mlx_win;
	char		*name;
	t_img		img;
}	t_minilibx;

typedef struct s_light
{
	t_point		pos;
	double		ratio;
	t_color		color;
}	t_light;

typedef struct s_amblight
{
	double		ratio;
	t_color		color;
}	t_amblight;

typedef struct camera
{
	t_point		pos;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_object
{
	t_type		type;
	t_point		pos;
	t_vector	orientation;
	double		diameter;
	double		height;
	t_color		color;
	double		shininess;
}	t_object;

typedef enum e_option
{
	NOTHING,
	X,
	Y,
	Z,
	D,
	H
}	t_option;

typedef struct t_data
{
	t_minilibx	*mlx_struct;
	t_light		light;
	t_amblight	ambient;
	t_camera	camera;
	t_object	*objects;
	int			num_of_objects;
	t_object	*selected_object;
	t_option	option;
}	t_data;

void			parsing(t_elem **elem, char *file, int argc);
void			read_check_assign(t_elem *elem, char *file, int *status);
int				get_num_of_elem(int fd);
bool			check_empty_line(char *line);
void			ft_free_split(char **split);
void			remove_next_line(char *line);
double			ft_atof(char *str);
bool			check_status(int *status, char **l_split);
void			check_assign_ambient(char **l_split, t_elem *elem, int *status);
int				ft_split_len(char **split);
bool			check_digits(char **l_split);
int				check_digits_advanced(char *str);
void			check_assign_camera(char **l_split, t_elem *elem, int *status);
void			check_assign_light(char **l_split, t_elem *elem, int *status);
int				validate_color_values(char **split_color, int *status,
					int type);
void			check_repitition(t_elem *elem, int *status);
void			check_assign_sphere(char **l_split, t_elem *elem, int *status);
void			check_assign_plane(char **l_split, t_elem *elem, int *status);
void			check_assign_cylinder(char **l_split, t_elem *elem,
					int *status);

t_vector		normalize(t_vector v);
t_vector		two_points_vect(t_point a, t_point b);
t_vector		axes_sum(t_axes a, t_axes b);
t_vector		axes_sub(t_axes a, t_axes b);
t_vector		cross_product(t_vector a, t_vector b);
t_vector		vect_mult(t_vector v, double a);
t_point			ray_point(t_point origin, t_vector direction, double t);
t_vector		reflect_ray(t_vector ray, t_vector normal);
double			dot_product(t_vector a, t_vector b);
double			vect_length2(t_vector v);

#endif
