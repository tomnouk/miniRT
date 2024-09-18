/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:06:10 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/18 11:17:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
