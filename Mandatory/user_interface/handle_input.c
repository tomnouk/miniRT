/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:02:40 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/09/28 12:39:43 by samy_bravy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	data->camera.orientation = normalize(data->camera.orientation);
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
			break ;
		if (str)
			free(str);
	}
	get_next_line(-1);
	return (str);
}
