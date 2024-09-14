/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/14 13:27:19 by samy_bravy       ###   ########.fr       */
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
	mlx_destroy_image(data->mlx_struct->mlx, data->mlx_struct->img.img);
	mlx_destroy_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win);
	mlx_destroy_display(data->mlx_struct->mlx);
	free(data->mlx_struct->mlx);
	free(data->objects);
	exit(EXIT_SUCCESS);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		esc(data);
	if (keycode == XK_q)
	{
		data->selected_object = NULL;
		data->option = NOTHING;
		mlx_put_image_to_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win, data->mlx_struct->img.img, 0, 0);
		return (0);
	}
	else if (keycode == XK_d && data->selected_object->type == sp && data->option == NOTHING)
	{
		data->option = D;
		mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 400, 14, 0x00FFFFFF, "Selected diameter");
		return (0);
	}
	else if (keycode == XK_h && data->selected_object->type == cy && data->option == NOTHING)
	{
		data->option = H;
		mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 400, 14, 0x00FFFFFF, "Selected height");
		return (0);
	}
	else if (keycode == XK_x && data->option == NOTHING)
	{
		data->option = X;
		mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 400, 14, 0x00FFFFFF, "Selected x");
		return (0);
	}
	else if (keycode == XK_y && data->option == NOTHING)
	{
		data->option = Y;
		mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 400, 14, 0x00FFFFFF, "Selected y");
		return (0);
	}
	else if (keycode == XK_z && data->option == NOTHING)
	{
		data->option = Z;
		mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 400, 14, 0x00FFFFFF, "Selected z");
		return (0);
	}
	else if (keycode == XK_plus)
	{
		if (data->option == D)
			data->selected_object->diameter *= 1.1;
		if (data->option == H)
			data->selected_object->height *= 1.1;
		if (data->option == X)
			data->selected_object->orientation.x += 1;
		if (data->option == Y)
			data->selected_object->orientation.y += 1;
		if (data->option == Z)
			data->selected_object->orientation.z += 1;
	}
	else if (keycode == XK_minus)
	{
		if (data->option == D)
			data->selected_object->diameter /= 1.1;
		if (data->option == H)
			data->selected_object->height /= 1.1;
		if (data->option == X)
			data->selected_object->orientation.x -= 1;
		if (data->option == Y)
			data->selected_object->orientation.y -= 1;
		if (data->option == Z)
			data->selected_object->orientation.z -= 1;
	}
	else if (keycode == XK_Up && data->selected_object != NULL)
		data->selected_object->pos.y += 1;
	else if (keycode == XK_Down && data->selected_object != NULL)
		data->selected_object->pos.y -= 1;
	else if (keycode == XK_Left && data->selected_object != NULL)
		data->selected_object->pos.x -= 1;
	else if (keycode == XK_Right && data->selected_object != NULL)
		data->selected_object->pos.x += 1;
	mlx_put_image_to_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win, data->mlx_struct->img.img, 0, 0);
	return (0);
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

t_vector	rotate_vector(t_vector v, t_vector orientation)
{
	t_vector	res;

	(void)orientation;
	res = v;
	return (res);
}

bool	sphere_intersection(t_point origin, t_vector direction,
	t_object *sphere, double *t)
{
	t_vector	co;
	double		b;
	double		c;
	double		delta;
	double		delta_sqrt;

	co = two_points_vect(sphere->pos, origin);
	b = 2 * dot_product(direction, co);
	c = vect_length2(co) - sphere->diameter * sphere->diameter / 4;
	delta = b * b - 4 * c;
	if (delta < 0)
		return (false);
	delta_sqrt = sqrt(delta);
	*t = (-b - delta_sqrt) / 2;
	if (*t <= 1.0e-6)
		*t = (-b + delta_sqrt) / 2;
	if (*t <= 1.0e-6)
		return (false);
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
		return (false);
	*t = -dot_product(p_o, plane->orientation) / d_dot_n;
	if (*t <= 1.0e-6)
		return (false);
	return (true);
}

bool	cylinder_intersection(t_point origin, t_vector direction,
	t_object *cylinder, double *t)
{
	(void)origin;
	(void)direction;
	(void)cylinder;
	(void)t;
	return (false);
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
	return (first_obj);
}

t_vector	calculate_cylinder_normal(t_object *cylinder, t_point p)
{
	(void)cylinder;
	(void)p;
	return ((t_vector){0, 0, 0});
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
		normal = calculate_cylinder_normal(obj, p);
	p_to_light = normalize(two_points_vect(p, data->light.pos));
	if (first_obj_hit(data, p, p_to_light, &(double){0}) != NULL)
		return (0);
	intensity = dot_product(normal, p_to_light);
	if (intensity < 0)
		intensity = 0;
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
	data.selected_object = NULL;
	data.option = NOTHING;
	data.light.pos = light.pos;
	data.light.ratio = light.ratio;
	data.light.color = light.color;
	data.ambient.ratio = ambient.ratio;
	data.ambient.color = ambient.color;
	data.camera.pos = camera.pos;
	data.camera.orientation = camera.orientation;
	data.camera.fov = camera.fov * M_PI / 180;
	build_objects(elem, &data);
	return (data);
}

void display_object_info(t_data *data)
{
	char	*str;

	if (data->selected_object->type == pl)
		str = "plane";
	else if (data->selected_object->type == sp)
		str = "sphere";
	else if (data->selected_object->type == cy)
		str = "cylinder";
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 59, 14, 0x00FFFFFF, str);
}

void display_object_position(t_data *data)
{
	char	*str;

	str = ft_itoa(data->selected_object->pos.x);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 150, 14, 0x00FFFFFF, str);
	free(str);
	str = ft_itoa(data->selected_object->pos.y);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 200, 14, 0x00FFFFFF, str);
	free(str);
	str = ft_itoa(data->selected_object->pos.z);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 250, 14, 0x00FFFFFF, str);
	free(str);
}

void display_controls(t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str3 = "";
	if (data->selected_object->type == sp)
	{
		data->option = D;
		str1 = "+/- to resize diameter";
		str2 = "arrows to move the sphere";
	}
	else if (data->selected_object->type == pl)
	{
		str1 = "arrows to move the plane";
		str2 = "x/y/z +/- to rotate the plane";
	}
	else if (data->selected_object->type == cy)
	{
		str1 = "d/h +/- to resize diameter/height";
		str2 = "arrows to move the cylinder";
		str3 = "x/y/z +/- to rotate the cylinder";
	}
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 10, 40, 0x00FFFFFF, str1);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 10, 60, 0x00FFFFFF, str2);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 10, 80, 0x00FFFFFF, str3);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 7, 100, 0x00FFFFFF, "q to unselect");
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	t_point		pixel_camera;
	t_point		origin;
	t_vector	direction;

	if (keycode != 1)
		return (0);
	data->option = NOTHING;
	mlx_put_image_to_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win, data->mlx_struct->img.img, 0, 0);
	pixel_camera = get_pixel_camera(data->camera.fov, x, y);
	get_camera_ray(data, pixel_camera, &origin, &direction);
	data->selected_object = first_obj_hit(data, origin, direction, &(double){0});
	if (data->selected_object == NULL)
		return (0);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win, 7, 14, 0x00FFFFFF, "Selected");
	display_object_info(data);
	display_object_position(data);
	display_controls(data);
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
	mlx_loop(mlx_struct.mlx);
	return (0);
}
