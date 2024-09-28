/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_properties_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:50:42 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/28 12:39:35 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

void	change_plane_properties(t_object *plane)
{
	prompt_and_set("Enter plane position x", &plane->pos.x);
	prompt_and_set("Enter plane position y", &plane->pos.y);
	prompt_and_set("Enter plane position z", &plane->pos.z);
	prompt_and_set("Enter plane normal vector x", &plane->orientation.x);
	prompt_and_set("Enter plane normal vector y", &plane->orientation.y);
	prompt_and_set("Enter plane normal vector z", &plane->orientation.z);
	plane->orientation = normalize(plane->orientation);
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
	cylinder->orientation = normalize(cylinder->orientation);
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
	if (!ft_strcmp(str, "L\n") && data->num_of_lights > 0)
	{
		free(str);
		printf("Insert index of light to move (0-%d)\n",
			data->num_of_lights - 1);
		str = get_next_line(STDIN_FILENO);
		if (str)
			if (ft_atoi(str) >= 0 && ft_atoi(str) < data->num_of_lights)
				set_light_position(&data->lights[ft_atoi(str)]);
		if (!str || ft_atoi(str) < 0 || ft_atoi(str) >= data->num_of_lights)
			printf("Invalid input, operation cancelled\n");
		get_next_line(-1);
	}
	else if (!ft_strcmp(str, "C\n"))
	{
		set_camera_position(data);
		set_camera_orientation(data);
	}
	if (str)
		free(str);
}
