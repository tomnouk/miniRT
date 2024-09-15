/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 02:47:31 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/15 18:14:48 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minirt.h"

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_color	mult_colors(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r / 255;
	res.g = a.g * b.g / 255;
	res.b = a.b * b.b / 255;
	return (res);
}

t_color	sum_colors(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_color	mult_color_ratio(t_color a, double ratio)
{
	t_color	res;

	res.r = a.r * ratio;
	res.g = a.g * ratio;
	res.b = a.b * ratio;
	return (res);
}

void	minilibx_init(t_minilibx *smlx, t_elem *elem)
{
	smlx->mlx = mlx_init();
	if (!smlx->mlx)
	{
		free(elem);
		exit(EXIT_FAILURE);
	}
	smlx->mlx_win = mlx_new_window(smlx->mlx, WIDTH, HEIGHT, smlx->name);
	if (!smlx->mlx_win)
	{
		mlx_destroy_display(smlx->mlx);
		free(smlx->mlx);
		free(elem);
		exit(EXIT_FAILURE);
	}
	smlx->img.img = mlx_new_image(smlx->mlx, WIDTH, HEIGHT);
	if (!smlx->img.img)
	{
		mlx_destroy_window(smlx->mlx, smlx->mlx_win);
		mlx_destroy_display(smlx->mlx);
		free(smlx->mlx);
		free(elem);
		exit(EXIT_FAILURE);
	}
	smlx->img.addr = mlx_get_data_addr(smlx->img.img, &smlx->img.bits_per_pixel,
			&smlx->img.line_length, &smlx->img.endian);
}

int	esc(t_data *data)
{
	if (data->changing_properties)
		return (0);
	mlx_destroy_image(data->mlx_struct->mlx, data->mlx_struct->img.img);
	mlx_destroy_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win);
	mlx_destroy_display(data->mlx_struct->mlx);
	free(data->mlx_struct->mlx);
	free(data->objects);
	exit(EXIT_SUCCESS);
}

void	before_digit(char *nptr, int *n, int *i)
{
	while ((nptr[*n] >= 9 && nptr[*n] <= 13) || nptr[*n] == ' ')
		*n += 1;
	if (nptr[*n] == '-' || nptr[*n] == '+')
	{
		if (nptr[*n] == '-')
			*i *= -1;
		*n += 1;
	}
}

double	my_ft_atof(char *nptr)
{
	int		i;
	int		n;
	int		dot;
	double	res;

	n = 0;
	i = 1;
	res = 0;
	before_digit(nptr, &n, &i);
	dot = 0;
	while ((nptr[n] >= '0' && nptr[n] <= '9') || nptr[n] == '.')
	{
		if (nptr[n] == '.')
			dot = 1;
		else if (!dot)
			res = res * 10 + (nptr[n] - '0');
		else
		{
			res += (nptr[n] - '0') / pow(10, dot);
			dot++;
		}
		n++;
	}
	return (res * i);
}

void	prompt_and_set(char *prompt, double *value)
{
	char	*str;

	while (true)
	{
		printf("%s\n", prompt);
		str = get_next_line(STDIN_FILENO);
		if (str)
		{
			str[strlen(str) - 1] = '\0';
			*value = my_ft_atof(str);
			free(str);
			break ;
		}
	}
	get_next_line(-1);
}

void	set_light_position(t_data *data)
{
	prompt_and_set("Enter light position x", &data->light.pos.x);
	prompt_and_set("Enter light position y", &data->light.pos.y);
	prompt_and_set("Enter light position z", &data->light.pos.z);
}

void	set_camera_position(t_data *data)
{
	prompt_and_set("Enter camera position x", &data->camera.pos.x);
	prompt_and_set("Enter camera position y", &data->camera.pos.y);
	prompt_and_set("Enter camera position z", &data->camera.pos.z);
}

void	set_camera_orientation(t_data *data)
{
	prompt_and_set("Enter camera orientation x", &data->camera.orientation.x);
	prompt_and_set("Enter camera orientation y", &data->camera.orientation.y);
	prompt_and_set("Enter camera orientation z", &data->camera.orientation.z);
}

char	*get_valid_input_ambient(void)
{
	char	*str;

	while (true)
	{
		printf("Insert L to move light\n");
		printf("Insert C to change camera properties\n");
		printf("Insert Q to quit\n");
		str = get_next_line(STDIN_FILENO);
		if (str && (!ft_strcmp(str, "L\n")
				|| !ft_strcmp(str, "C\n")
				|| !ft_strcmp(str, "Q\n")))
			return (str);
		free(str);
	}
	get_next_line(-1);
}

void	change_plane_properties(t_object *plane)
{
	prompt_and_set("Enter plane position x", &plane->pos.x);
	prompt_and_set("Enter plane position y", &plane->pos.y);
	prompt_and_set("Enter plane position z", &plane->pos.z);
	prompt_and_set("Enter plane normal vector x", &plane->orientation.x);
	prompt_and_set("Enter plane normal vector y", &plane->orientation.y);
	prompt_and_set("Enter plane normal vector z", &plane->orientation.z);
}

void	change_sphere_properties(t_object *sphere)
{
	prompt_and_set("Enter sphere center x", &sphere->pos.x);
	prompt_and_set("Enter sphere center y", &sphere->pos.y);
	prompt_and_set("Enter sphere center z", &sphere->pos.z);
	prompt_and_set("Enter sphere diameter", &sphere->diameter);
}

void	change_cylinder_properties(t_object *cylinder)
{
	prompt_and_set("Enter cylinder center x", &cylinder->pos.x);
	prompt_and_set("Enter cylinder center y", &cylinder->pos.y);
	prompt_and_set("Enter cylinder center z", &cylinder->pos.z);
	prompt_and_set("Enter cylinder orientation vector x",
		&cylinder->orientation.x);
	prompt_and_set("Enter cylinder orientation vector y",
		&cylinder->orientation.y);
	prompt_and_set("Enter cylinder orientation vector z",
		&cylinder->orientation.z);
	prompt_and_set("Enter cylinder diameter", &cylinder->diameter);
	prompt_and_set("Enter cylinder height", &cylinder->height);
}

void	change_object_properties(t_data *data)
{
	if (data->selected_obj->type == pl)
		change_plane_properties(data->selected_obj);
	else if (data->selected_obj->type == sp)
		change_sphere_properties(data->selected_obj);
	else if (data->selected_obj->type == cy)
		change_cylinder_properties(data->selected_obj);
}

void	change_ambient_properties(t_data *data)
{
	char	*str;

	str = get_valid_input_ambient();
	if (!ft_strcmp(str, "L\n"))
		set_light_position(data);
	else if (!ft_strcmp(str, "C\n"))
	{
		set_camera_position(data);
		set_camera_orientation(data);
	}
	free(str);
}

t_elem	*get_type_element(t_elem *elem, t_type type)
{
	while (elem->type != NONE)
	{
		if (elem->type == type)
			return (elem);
		elem++;
	}
	return (NULL);
}

t_vector	rotate_vector(t_vector v, t_vector direction)
{
	t_vector	axis;
	double		angle;
	double		cos_angle;
	double		sin_angle;
	t_vector	rotated;

	angle = acos(direction.z);
	axis = cross_product((t_vector){0, 0, 1}, direction);
	axis = normalize(axis);
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	rotated.x = (axis.x * axis.x + (1 - axis.x * axis.x) * cos_angle) * v.x
		+ ((1 - cos_angle) * axis.x * axis.y - sin_angle * axis.z) * v.y
		+ ((1 - cos_angle) * axis.x * axis.z + sin_angle * axis.y) * v.z;
	rotated.y = ((1 - cos_angle) * axis.x * axis.y + sin_angle * axis.z) * v.x
		+ (axis.y * axis.y + (1 - axis.y * axis.y) * cos_angle) * v.y
		+ ((1 - cos_angle) * axis.y * axis.z - sin_angle * axis.x) * v.z;
	rotated.z = ((1 - cos_angle) * axis.x * axis.z - sin_angle * axis.y) * v.x
		+ ((1 - cos_angle) * axis.y * axis.z + sin_angle * axis.x) * v.y
		+ (axis.z * axis.z + (1 - axis.z * axis.z) * cos_angle) * v.z;
	return (rotated);
}

bool	quadratic_equation(double a, double b, double c, double t[2])
{
	double	delta;
	double	delta_sqrt;

	delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		t[0] = 0;
		t[1] = 0;
		return (false);
	}
	delta_sqrt = sqrt(delta);
	t[0] = (-b - delta_sqrt) / (2 * a);
	t[1] = (-b + delta_sqrt) / (2 * a);
	return (true);
}

bool	sphere_intersection(t_point origin, t_vector direction,
	t_object *sphere, double *t)
{
	t_vector	co;
	double		b;
	double		c;
	double		possible_t[2];

	co = two_points_vect(sphere->pos, origin);
	b = 2 * dot_product(direction, co);
	c = vect_length2(co) - sphere->diameter * sphere->diameter / 4;
	if (!quadratic_equation(1, b, c, possible_t))
	{
		*t = 0;
		return (false);
	}
	if (possible_t[0] > PRECISION)
		*t = possible_t[0];
	else if (possible_t[1] > PRECISION)
		*t = possible_t[1];
	else
	{
		*t = 0;
		return (false);
	}
	return (true);
}

bool	plane_intersection(t_point origin, t_vector direction,
	t_object *plane, double *t)
{
	t_vector	p_o;
	double		d_dot_n;

	p_o = two_points_vect(plane->pos, origin);
	d_dot_n = dot_product(direction, plane->orientation);
	if (d_dot_n == 0)
	{
		*t = 0;
		return (false);
	}
	*t = -dot_product(p_o, plane->orientation) / d_dot_n;
	if (*t <= PRECISION)
		return (false);
	return (true);
}

bool	is_tape_t(double possible_t, t_object *cylinder, t_vector co,
	t_vector direction)
{
	if (possible_t > PRECISION
		&& vect_length(axes_sub(ray_point(co, direction, possible_t),
				vect_mult(cylinder->orientation, cylinder->height / 2)))
		<= cylinder->diameter / 2)
		return (true);
	return (false);
}

bool	is_body_t(double possible_t, t_object *cylinder, t_vector co,
	t_vector direction)
{
	if (possible_t > PRECISION
		&& ft_abs(dot_product(ray_point(co, direction, possible_t),
				cylinder->orientation)) <= cylinder->height / 2)
		return (true);
	return (false);
}

bool	t_minor(double t, double t_min)
{
	if (t < t_min || t_min <= PRECISION)
	{
		t_min = t;
		return (true);
	}
	return (false);
}

double	get_lowest_t_tape(t_object *cylinder, t_vector co, t_vector direction,
	t_point origin)
{
	double		t;
	double		possible_t;
	t_vector	half_height_vect;
	t_point		c1;
	t_point		c2;

	half_height_vect = vect_mult(cylinder->orientation,
			cylinder->height / 2);
	c1 = axes_sum(cylinder->pos, half_height_vect);
	c2 = axes_sub(cylinder->pos, half_height_vect);
	t = 0;
	plane_intersection(origin, direction,
		&(t_object){pl, c1, cylinder->orientation, 0, 0, cylinder->color, 0},
		&possible_t);
	if (is_tape_t(possible_t, cylinder, co, direction))
		t = possible_t;
	plane_intersection(origin, direction,
		&(t_object){pl, c2, cylinder->orientation, 0, 0, cylinder->color, 0},
		&possible_t);
	if (is_tape_t(possible_t, cylinder,
			vect_mult(co, -1), vect_mult(direction, -1))
		&& t_minor(possible_t, t))
		t = possible_t;
	return (t);
}

double	get_lowest_t_body(t_object *cylinder, t_vector co, t_vector direction)
{
	double		t;
	double		abc[3];
	double		possible_t[2];
	t_vector	normal_ray;
	t_vector	normal_center;

	normal_ray = axes_sub(direction, vect_mult(cylinder->orientation,
				dot_product(direction, cylinder->orientation)));
	normal_center = axes_sub(co, vect_mult(cylinder->orientation,
				dot_product(co, cylinder->orientation)));
	abc[0] = vect_length2(normal_ray);
	abc[1] = 2 * dot_product(normal_ray, normal_center);
	abc[2] = vect_length2(normal_center)
		- cylinder->diameter * cylinder->diameter / 4;
	t = 0;
	if (quadratic_equation(abc[0], abc[1], abc[2], possible_t))
	{
		if (is_body_t(possible_t[0], cylinder, co, direction))
			t = possible_t[0];
		if (is_body_t(possible_t[1], cylinder, co, direction)
			&& t_minor(possible_t[1], t))
			t = possible_t[1];
	}
	return (t);
}

bool	cylinder_intersection(t_point origin, t_vector direction,
	t_object *cylinder, double *t)
{
	t_vector	co;
	double		possible_t;

	co = two_points_vect(cylinder->pos, origin);
	*t = get_lowest_t_body(cylinder, co, direction);
	possible_t = get_lowest_t_tape(cylinder, co, direction, origin);
	if (possible_t > PRECISION && t_minor(possible_t, *t))
		*t = possible_t;
	return (*t > PRECISION);
}

t_object	*first_obj_hit(t_data *data, t_point origin, t_vector direction,
	double *t)
{
	t_object	*first_obj;
	double		t_min;
	int			i;

	first_obj = NULL;
	i = 0;
	while (i < data->num_of_objects)
	{
		if ((data->objects[i].type == sp && sphere_intersection(origin,
					direction, &data->objects[i], t))
			|| (data->objects[i].type == pl && plane_intersection(origin,
					direction, &data->objects[i], t))
			|| (data->objects[i].type == cy && cylinder_intersection(origin,
					direction, &data->objects[i], t)))
		{
			if (first_obj == NULL || *t < t_min)
			{
				t_min = *t;
				first_obj = &data->objects[i];
			}
		}
		i++;
	}
	*t = t_min;
	return (first_obj);
}

t_vector	calculate_cylinder_normal(t_object *cylinder, t_vector direction,
	t_point origin)
{
	double		t_tape;
	double		t_body;
	t_vector	co;
	t_vector	dir_on_axis_proj;

	co = two_points_vect(cylinder->pos, origin);
	t_tape = get_lowest_t_tape(cylinder, co, direction, origin);
	t_body = get_lowest_t_body(cylinder, co, direction);
	if (t_tape > PRECISION && (t_tape < t_body || t_body <= PRECISION))
	{
		if (dot_product(direction, cylinder->orientation) > 0)
			return (normalize(cylinder->orientation));
		return (normalize(vect_mult(cylinder->orientation, -1)));
	}
	dir_on_axis_proj = vect_mult(cylinder->orientation,
			dot_product(direction, cylinder->orientation));
	return (normalize(axes_sub(dir_on_axis_proj, direction)));
}

bool	hit_obj_before_light(t_data *data, t_point p, t_vector p_to_light)
{
	double	t_obj;

	if (first_obj_hit(data, p, p_to_light, &t_obj) != NULL
		&& t_obj < vect_length(two_points_vect(p, data->light.pos)))
		return (true);
	return (false);
}

double	light_intensity(t_data *data, t_vector direction, t_point p,
	t_object *obj)
{
	t_vector	normal;
	t_vector	p_to_light;
	double		intensity;

	if (obj->type == pl)
		normal = obj->orientation;
	else if (obj->type == sp)
		normal = normalize(two_points_vect(obj->pos, p));
	else if (obj->type == cy)
		normal = calculate_cylinder_normal(obj, direction, data->camera.pos);
	p_to_light = normalize(two_points_vect(p, data->light.pos));
	if (hit_obj_before_light(data, p, p_to_light))
		return (0);
	intensity = dot_product(normal, p_to_light);
	if (intensity < 0)
		intensity *= -1;
	if (obj->shininess > 0)
	{
		intensity += pow(dot_product(direction,
					reflect_ray(p_to_light, normal)), obj->shininess);
		if (intensity < 0)
			intensity = 0;
	}
	return (intensity * data->light.ratio);
}

void	get_camera_ray(t_data *data, t_point pixel_camera,
	t_point *origin, t_vector *direction)
{
	*origin = (t_point){0, 0, 0};
	*direction = normalize(two_points_vect(*origin, pixel_camera));
	*origin = axes_sum(*origin, data->camera.pos);
	*direction = rotate_vector(*direction, data->camera.orientation);
}

int	build_ray(t_data *data, t_point pixel_camera)
{
	t_point		origin;
	t_vector	direction;
	t_object	*obj;
	t_color		color;
	double		t;

	get_camera_ray(data, pixel_camera, &origin, &direction);
	obj = first_obj_hit(data, origin, direction, &t);
	if (obj == NULL)
		return (create_trgb(0, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
	color = mult_color_ratio(data->ambient.color, data->ambient.ratio);
	color = sum_colors(color,
			mult_color_ratio(data->light.color,
				light_intensity(data, direction,
					ray_point(origin, direction, t), obj)));
	color = mult_colors(color, obj->color);
	return (create_trgb(0, color.r, color.g, color.b));
}

t_point	get_pixel_camera(double fov, int x, int y)
{
	double	pixel_camera_x;
	double	pixel_camera_y;

	pixel_camera_x = (2 * (x + 0.5) / (double)WIDTH - 1)
		* tan(fov / 2) * WIDTH / HEIGHT;
	pixel_camera_y = (1 - 2 * (y + 0.5) / (double)HEIGHT)
		* tan(fov / 2);
	return ((t_point){pixel_camera_x, pixel_camera_y, 1});
}

void	build_image(t_data *data)
{
	int		color;
	int		x;
	int		y;
	t_point	pixel_camera;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_camera = get_pixel_camera(data->camera.fov, x, y);
			color = build_ray(data, pixel_camera);
			my_mlx_pixel_put(&data->mlx_struct->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	build_objects(t_elem *elem, t_data *data)
{
	int	i;

	data->num_of_objects = 0;
	i = -1;
	while (elem[++i].type != NONE)
	{
		if (elem[i].type == pl || elem[i].type == sp || elem[i].type == cy)
			data->num_of_objects++;
	}
	data->objects = malloc(sizeof(t_object) * data->num_of_objects);
	i = 0;
	while (elem->type != NONE)
	{
		if (elem->type == pl || elem->type == sp || elem->type == cy)
		{
			data->objects[i].type = elem->type;
			data->objects[i].pos = elem->pos;
			data->objects[i].orientation = elem->orientation;
			data->objects[i].diameter = elem->diameter;
			data->objects[i].height = elem->height;
			data->objects[i].color = elem->color;
			data->objects[i++].shininess = 40;
		}
		elem++;
	}
}

t_elem	find_elem(t_elem *elem, t_type type)
{
	while (elem->type != NONE)
	{
		if (elem->type == type)
			return (*elem);
		elem++;
	}
	return (*elem);
}

t_data	build_data(t_elem *elem, t_minilibx *mlx_struct)
{
	t_data	data;
	t_elem	camera;
	t_elem	light;
	t_elem	ambient;

	data.mlx_struct = mlx_struct;
	camera = find_elem(elem, C);
	light = find_elem(elem, L);
	ambient = find_elem(elem, A);
	data.light.pos = light.pos;
	data.light.ratio = light.ratio;
	data.light.color = light.color;
	data.ambient.ratio = ambient.ratio;
	data.ambient.color = ambient.color;
	data.camera.pos = camera.pos;
	data.camera.orientation = camera.orientation;
	data.camera.fov = camera.fov * M_PI / 180;
	build_objects(elem, &data);
	data.selected_obj = NULL;
	data.changing_properties = false;
	return (data);
}

void	display_value(t_data *data, double value, char *label, int y_offset)
{
	char	*str;

	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, y_offset, 0x00FFFFFF, label);
	str = ft_ftoa(value);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		180, y_offset, 0x00FFFFFF, str);
	free(str);
}

void	display_axes(t_data *data, t_axes axes, char *label, int y_offset)
{
	char	*str;

	display_value(data, axes.x, label, y_offset);
	str = ft_ftoa(axes.y);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		280, y_offset, 0x00FFFFFF, str);
	free(str);
	str = ft_ftoa(axes.z);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		380, y_offset, 0x00FFFFFF, str);
	free(str);
}

void	display_ambient_properties(t_data *data)
{
	display_axes(data, data->light.pos, "Light position:", 14);
	display_axes(data, data->camera.pos, "Camera position:", 33);
	display_axes(data, data->camera.orientation, "Camera orientation:", 49);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 73, 0x00FFFFFF, "Press C to change properties");
}

void	display_sphere_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Center:", 35);
	display_value(data, obj->diameter, "Diameter:", 50);
}

void	display_plane_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Point:", 35);
	display_axes(data, obj->orientation, "Normal:", 50);
}

void	display_cylinder_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Center:", 35);
	display_axes(data, obj->orientation, "Axis:", 50);
	display_value(data, obj->diameter, "Diameter:", 65);
	display_value(data, obj->height, "Height:", 80);
}

void	display_object_properties(t_data *data, t_object *obj)
{
	char	*str;

	if (obj->type == pl)
		str = "Plane";
	else if (obj->type == sp)
		str = "Sphere";
	else if (obj->type == cy)
		str = "Cylinder";
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 14, 0x00FFFFFF, str);
	if (obj->type == sp)
		display_sphere_properties(data, obj);
	else if (obj->type == pl)
		display_plane_properties(data, obj);
	else if (obj->type == cy)
	{
		display_cylinder_properties(data, obj);
	}
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 74 + 31 * (obj->type == cy), 0x00FFFFFF,
		"Press C to change properties");
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 90 + 31 * (obj->type == cy), 0x00FFFFFF,
		"Press Q to unselct object");
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	t_point		pixel_camera;
	t_point		origin;
	t_vector	direction;

	if (keycode != 1 || data->changing_properties == true)
		return (0);
	mlx_put_image_to_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		data->mlx_struct->img.img, 0, 0);
	pixel_camera = get_pixel_camera(data->camera.fov, x, y);
	get_camera_ray(data, pixel_camera, &origin, &direction);
	data->selected_obj = first_obj_hit(data, origin, direction, &(double){0});
	if (data->selected_obj == NULL)
	{
		display_ambient_properties(data);
		return (0);
	}
	display_object_properties(data, data->selected_obj);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	if (data->changing_properties)
		return (0);
	if (keycode == XK_Escape)
		esc(data);
	if (keycode == XK_c)
	{
		data->changing_properties = true;
		if (data->selected_obj == NULL)
			change_ambient_properties(data);
		else
			change_object_properties(data);
	}
	else if (keycode != XK_q)
		return (0);
	if (keycode == XK_c)
		build_image(data);
	mlx_put_image_to_window(data->mlx_struct->mlx,
		data->mlx_struct->mlx_win, data->mlx_struct->img.img, 0, 0);
	display_ambient_properties(data);
	data->selected_obj = NULL;
	data->changing_properties = false;
	return (0);
}

int	main(int argc, char **argv)
{
	t_elem		*elem;
	t_minilibx	mlx_struct;
	t_data		data;

	elem = NULL;
	parsing(&elem, argv[1], argc);
	mlx_struct.name = argv[1];
	minilibx_init(&mlx_struct, elem);
	data = build_data(elem, &mlx_struct);
	free(elem);
	build_image(&data);
	mlx_put_image_to_window(mlx_struct.mlx, mlx_struct.mlx_win,
		mlx_struct.img.img, 0, 0);
	mlx_hook(mlx_struct.mlx_win, 2, 1L << 0, key_down, &data);
	mlx_hook(mlx_struct.mlx_win, 17, 0L, esc, &data);
	mlx_mouse_hook(mlx_struct.mlx_win, mouse_hook, &data);
	display_ambient_properties(&data);
	mlx_loop(mlx_struct.mlx);
	return (0);
}
