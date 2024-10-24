/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:52:24 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/10/24 13:06:37 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
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
# define ERROR_REPETITION "Error\nRepetition of elements\n"
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
# define ERROR_PARABOLOID "Error\nInvalid paraboloid\n"
# define ERROR_PARABOLOID_PARAMS "Error\nInvalid paraboloid parameters\n"
# define ERROR_PARABOLOID_DIAMETER "Error\nInvalid paraboloid diameter\n"
# define ERROR_PARABOLOID_COLOR "Error\nInvalid paraboloid color\n"
# define ER_PARABOLOID_COLOR_VALUE "Error\nInvalid paraboloid color value\n"

# define WIDTH 1240
# define HEIGHT 860
# define PRECISION 1.0e-6
# define BACKGROUND_R 0
# define BACKGROUND_G 0
# define BACKGROUND_B 0

typedef enum type
{
	NONE,
	A,
	C,
	L,
	pl,
	sp,
	cy,
	h_p
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
	double		h_p_abcdefg[7];
	double		shininess;
}				t_elem;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_minilibx
{
	void		*mlx;
	void		*mlx_win;
	char		*name;
	t_img		img;
}				t_minilibx;

typedef struct s_light
{
	t_point		pos;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_amblight
{
	double		ratio;
	t_color		color;
}				t_amblight;

typedef struct camera
{
	t_point		pos;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef enum e_h_p_params
{
	pA,
	pB,
	pC,
	pD,
	pE,
	pF,
	pG
}				t_h_p_params;

typedef struct s_object
{
	t_type		type;
	t_point		pos;
	t_vector	orientation;
	double		diameter;
	double		height;
	double		h_p_abcdefg[7];
	t_color		color;
	double		shininess;
}				t_object;

typedef struct t_data
{
	t_minilibx	*mlx_struct;
	t_amblight	ambient;
	t_camera	camera;
	t_light		*lights;
	int			num_of_lights;
	t_object	*objects;
	int			num_of_objects;
	t_object	*selected_obj;
	bool		changing_properties;
}				t_data;

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
void			check_repetition(t_elem *elem, int *status);
void			check_assign_sphere(char **l_split, t_elem *elem, int *status);
void			check_assign_plane(char **l_split, t_elem *elem, int *status);
void			check_assign_cylinder(char **l_split, t_elem *elem,
					int *status);

t_point			ray_point(t_point origin, t_vector direction, double t);
t_vector		reflect_ray(t_vector ray, t_vector normal);
t_vector		two_points_vect(t_point a, t_point b);
t_vector		rotate_vector(t_vector v, t_vector direction);

t_vector		axes_sum(t_axes a, t_axes b);
t_vector		axes_sub(t_axes a, t_axes b);
t_vector		cross_product(t_vector a, t_vector b);
t_vector		vect_mult(t_vector v, double a);
double			dot_product(t_vector a, t_vector b);

t_vector		normalize(t_vector v);
double			vect_length(t_vector v);
double			vect_length2(t_vector v);

void			change_plane_properties(t_object *plane);
void			change_sphere_properties(t_object *sphere);
void			change_cylinder_properties(t_object *cylinder);
void			change_object_properties(t_data *data);
void			change_ambient_properties(t_data *data);

int				create_trgb(unsigned char t, unsigned char r, unsigned char g,
					unsigned char b);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_color			mult_colors(t_color a, t_color b);
t_color			sum_colors(t_color a, t_color b);
t_color			mult_color_ratio(t_color a, double ratio);

void			display_object_properties(t_data *data, t_object *obj);
void			display_ambient_properties(t_data *data);

char			*get_valid_input_ambient(void);
void			set_camera_orientation(t_data *data);
void			set_camera_position(t_data *data);
void			set_light_position(t_light *light);
void			prompt_and_set(char *prompt, double *value);

int				esc(t_data *data);
int				mouse_hook(int keycode, int x, int y, t_data *data);
int				key_down(int keycode, t_data *data);

bool			sphere_intersection(t_point origin, t_vector direction,
					t_object *sphere, double *t);
bool			plane_intersection(t_point origin, t_vector direction,
					t_object *plane, double *t);
bool			cylinder_intersection(t_point origin, t_vector direction,
					t_object *cylinder, double *t);
double			get_lowest_t_tape(t_object *cylinder, t_vector co,
					t_vector direction, t_point origin);
double			get_lowest_t_body(t_object *cylinder, t_vector co,
					t_vector direction);

bool			hy_parab_intersection(t_point origin, t_vector direction,
					t_object *h_paraboloid, double *t);

void			pa_is_zero(double h_p_abcdefg[7], t_point *vertex);
void			nothing_is_zero(double h_p_abcdefg[7], t_point *vertex);
void			c_is_not_zero(double h_p_abcdefg[7], t_point *vertex);

bool			quadratic_equation(double a, double b, double c, double t[2]);
bool			is_tape_t(double possible_t, t_object *cylinder, t_vector co,
					t_vector direction);
bool			is_body_t(double possible_t, t_object *cylinder, t_vector co,
					t_vector direction);
bool			t_minor(double t, double t_min);

double			my_ft_atof(char *nptr);
t_elem			find_elem(t_elem *elem, t_type type);
void			display_value(t_data *data, double value, char *label,
					int y_offset);
void			display_axes(t_data *data, t_axes axes, char *label,
					int y_offset);

t_color			total_light_color(t_data *data, t_vector direction, t_point p,
					t_object *obj);

t_object		*first_obj_hit(t_data *data, t_point origin, t_vector direction,
					double *t);
void			get_camera_ray(t_data *data, t_point pixel_camera,
					t_point *origin, t_vector *direction);
t_point			get_pixel_camera(double fov, int x, int y);
void			build_image(t_data *data);
void			assigning_if_one_char(char *string, int *status, t_elem *elem);
void			assigning_if_more_chars(char *string, int *status,
					t_elem *elem);
void			check_assign_paraboloid(char **l_split, t_elem *elem,
					int *status);
#endif
