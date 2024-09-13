/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/13 18:25:59 by sdell-er         ###   ########.fr       */
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

	res.x = (1 - orientation.y * orientation.y * (1 - orientation.z)) * v.x
		- orientation.x * orientation.y * (1 - orientation.z) * v.y
		+ orientation.x * v.z;
	res.y = -orientation.x * orientation.y * (1 - orientation.z) * v.x
		+ (1 - orientation.x * orientation.x * (1 - orientation.z)) * v.y
		+ orientation.y * v.z;
	res.z = -orientation.x * v.x
		- orientation.y * v.y
		+ orientation.z * v.z;
	return (res);
}

bool	sphere_intersection(t_point origin, t_vector direction,
	t_object *sphere, double *t)
{
	
}

bool	plane_intersection(t_point origin, t_vector direction,
	t_object *plane, double *t)
{
	
}

bool	cylinder_intersection(t_point origin, t_vector direction,
	t_object *cylinder, double *t)
{
	
}

t_object	*first_obj_hit(t_data *data, t_point origin, t_vector direction)
{
	t_object	*first_obj;
	double		t_min;
	double		t;
	int			i;

	first_obj = NULL;
	i = 0;
	while (i < data->num_of_objects)
	{
		if ((data->objects[i].type == sp && sphere_intersection(origin,
					direction, &data->objects[i], &t))
			|| (data->objects[i].type == pl && plane_intersection(origin,
					direction, &data->objects[i], &t))
			|| (data->objects[i].type == cy && cylinder_intersection(origin,
					direction, &data->objects[i], &t)))
		{
			if (first_obj == NULL || t < t_min)
			{
				t_min = t;
				first_obj = &data->objects[i];
			}
		}
		i++;
	}
	return (first_obj);
}

int	build_ray(t_data *data, t_point pixel_camera)
{
	t_point		origin;
	t_vector	direction;
	t_object	*obj;

	origin = (t_point){0, 0, 0};
	direction = normalize(two_points_vect(origin, pixel_camera));
	origin = axes_sum(origin, data->camera.pos);
	direction = rotate_vector(direction, data->camera.orientation);
	obj = first_obj_hit(data, origin, direction);
	if (obj == NULL)
		return (create_trgb(0, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
	return (create_trgb(0, obj->color.r, obj->color.g, obj->color.b));
}

void	build_image(t_data *data)
{
	int		color;
	int		x;
	int		y;
	double	pixel_camera_x;
	double	pixel_camera_y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_camera_x = (2 * (2 * (x + 0.5) / WIDTH - 1) - 1)
				* WIDTH / (double)HEIGHT * tan(data->camera.fov / 2.0);
			pixel_camera_y = (1 - 2 * (2 * (y + 0.5) / HEIGHT - 1))
				* tan(data->camera.fov / 2.0);
			color = build_ray(data,
					(t_point){pixel_camera_x, pixel_camera_y, 1});
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
			i++;
		}
		elem++;
	}
}

t_data	build_data(t_elem *elem, t_minilibx *mlx_struct)
{
	t_data	data;

	data.mlx_struct = mlx_struct;
	data.light = (t_light){elem->pos, elem->ratio, elem->color};
	data.ambient = (t_amblight){elem->ratio, elem->color};
	data.camera = (t_camera){elem->pos, elem->orientation,
		(double)elem->fov * M_PI / 180};
	build_objects(elem, &data);
	return (data);
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
	mlx_loop(mlx_struct.mlx);
	return (0);
}
