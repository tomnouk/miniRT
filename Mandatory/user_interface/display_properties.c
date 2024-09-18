/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:57:13 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/18 11:13:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	display_ambient_properties(t_data *data)
{
	display_axes(data, data->light.pos, "Light position:", 14);
	display_axes(data, data->camera.pos, "Camera position:", 33);
	display_axes(data, data->camera.orientation, "Camera orientation:", 49);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 73, 0x00FFFFFF, "Press C to change properties");
}

static void	display_sphere_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Center:", 35);
	display_value(data, obj->diameter, "Diameter:", 50);
}

static void	display_plane_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Point:", 35);
	display_axes(data, obj->orientation, "Normal:", 50);
}

static void	display_cylinder_properties(t_data *data, t_object *obj)
{
	display_axes(data, obj->pos, "Center:", 35);
	display_axes(data, obj->orientation, "Axis:", 50);
	display_value(data, obj->diameter, "Diameter:", 65);
	display_value(data, obj->height, "Height:", 80);
}

void	display_object_properties(t_data *data, t_object *obj)
{
	char	*str;

	str = "";
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
