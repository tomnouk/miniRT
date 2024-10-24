/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 02:47:31 by samy_bravy        #+#    #+#             */
/*   Updated: 2024/10/24 12:59:23 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	build_objects(t_elem *elem, t_data *data)
{
	int	i;

	data->objects = malloc(sizeof(t_object) * data->num_of_objects);
	i = 0;
	while (elem->type != NONE)
	{
		if (elem->type == pl || elem->type == sp
			|| elem->type == cy || elem->type == h_p)
		{
			data->objects[i].type = elem->type;
			data->objects[i].pos = elem->pos;
			data->objects[i].orientation = normalize(elem->orientation);
			data->objects[i].diameter = elem->diameter;
			data->objects[i].height = elem->height;
			ft_memcpy(data->objects[i].h_p_abcdefg, elem->h_p_abcdefg,
				sizeof(double) * 7);
			data->objects[i].color = elem->color;
			data->objects[i++].shininess = 28;
		}
		elem++;
	}
}

static void	build_lights(t_elem *elem, t_data *data)
{
	int	i;

	data->num_of_lights = 0;
	i = -1;
	while (elem[++i].type != NONE)
	{
		if (elem[i].type == L)
			data->num_of_lights++;
	}
	data->lights = malloc(sizeof(t_light) * data->num_of_lights);
	i = 0;
	while (elem->type != NONE)
	{
		if (elem->type == L)
		{
			data->lights[i].pos = elem->pos;
			data->lights[i].ratio = elem->ratio;
			data->lights[i++].color = elem->color;
		}
		elem++;
	}
}

static t_data	build_data(t_elem *elem, t_minilibx *mlx_struct)
{
	t_data			data;
	t_elem			camera;
	t_elem			ambient;
	static int		i = -1;

	data.mlx_struct = mlx_struct;
	camera = find_elem(elem, C);
	ambient = find_elem(elem, A);
	data.ambient.ratio = ambient.ratio;
	data.ambient.color = ambient.color;
	data.camera.pos = camera.pos;
	data.camera.orientation = normalize(camera.orientation);
	if (camera.fov == 180)
		camera.fov = 179.9;
	data.camera.fov = camera.fov * M_PI / 180;
	build_lights(elem, &data);
	data.num_of_objects = 0;
	while (elem[++i].type != NONE)
		if (elem[i].type == pl || elem[i].type == sp
			|| elem[i].type == cy || elem[i].type == h_p)
			data.num_of_objects++;
	build_objects(elem, &data);
	data.selected_obj = NULL;
	data.changing_properties = false;
	return (data);
}

static void	minilibx_init(t_minilibx *smlx, t_elem *elem)
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
