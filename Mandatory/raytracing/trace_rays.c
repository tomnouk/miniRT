/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:31:26 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/28 11:50:30 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_object	*first_obj_hit(t_data *data, t_point origin, t_vector direction,
	double *t)
{
	t_object	*first_obj;
	double		t_min;
	int			i;

	first_obj = NULL;
	i = -1;
	t_min = 0;
	while (++i < data->num_of_objects)
	{
		if ((data->objects[i].type == sp && sphere_intersection(origin,
					direction, &data->objects[i], t))
			|| (data->objects[i].type == pl && plane_intersection(origin,
					direction, &data->objects[i], t))
			|| (data->objects[i].type == cy && cylinder_intersection(origin,
					direction, &data->objects[i], t)))
		{
			if (first_obj == NULL || (*t < t_min || t_min == 0))
			{
				t_min = *t;
				first_obj = &data->objects[i];
			}
		}
	}
	*t = t_min;
	return (first_obj);
}

void	get_camera_ray(t_data *data, t_point pixel_camera,
	t_point *origin, t_vector *direction)
{
	*origin = (t_point){0, 0, 0};
	*direction = normalize(two_points_vect(*origin, pixel_camera));
	*origin = axes_sum(*origin, data->camera.pos);
	*direction = rotate_vector(*direction, data->camera.orientation);
}

t_point	get_pixel_camera(double fov, int x, int y)
{
	double	pixel_camera_x;
	double	pixel_camera_y;
	double	tan_half_fov;

	tan_half_fov = tan(fov / 2);
	pixel_camera_x = (2 * (x + 0.5) / (double)WIDTH - 1)
		* tan_half_fov * WIDTH / HEIGHT;
	pixel_camera_y = (1 - 2 * (y + 0.5) / (double)HEIGHT)
		* tan_half_fov;
	return ((t_point){pixel_camera_x, pixel_camera_y, 1});
}

static int	build_ray(t_data *data, t_point pixel_camera)
{
	t_point		origin;
	t_vector	direction;
	t_object	*obj;
	t_color		color;
	double		t;

	get_camera_ray(data, pixel_camera, &origin, &direction);
	obj = first_obj_hit(data, origin, direction, &t);
	if (obj == NULL || t < PRECISION)
		return (create_trgb(0, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B));
	color = mult_color_ratio(data->ambient.color, data->ambient.ratio);
	color = sum_colors(color,
			mult_color_ratio(data->light.color,
				light_intensity(data, direction,
					ray_point(origin, direction, t), obj)));
	color = mult_colors(color, obj->color);
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (create_trgb(0, color.r, color.g, color.b));
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
