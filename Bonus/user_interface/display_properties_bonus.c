/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_properties_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:57:13 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/23 08:27:03 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	display_ambient_properties(t_data *data)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (++i < data->num_of_lights)
	{
		str = ft_itoa(i);
		tmp = ft_strjoin("Light ", str);
		free(str);
		str = ft_strjoin(tmp, " position:");
		free(tmp);
		display_axes(data, data->lights[i].pos, str, 14 + 16 * i);
		free(str);
	}
	i--;
	display_axes(data, data->camera.pos, "Camera position:", 33 + 16 * i);
	display_axes(data, data->camera.orientation,
		"Camera orientation:", 49 + 16 * i);
	mlx_string_put(data->mlx_struct->mlx, data->mlx_struct->mlx_win,
		7, 73 + 16 * i, 0x00FFFFFF, "Press C to change properties");
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
