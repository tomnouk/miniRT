/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy_bravy <samy_bravy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:01:41 by aeid              #+#    #+#             */
/*   Updated: 2024/09/13 00:00:19 by samy_bravy       ###   ########.fr       */
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

void	minilibx_init(t_minilibx *s_mlx, t_elem *elem)
{
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
	{
		free(elem);
		exit(EXIT_FAILURE);
	}
	s_mlx->mlx_win = mlx_new_window(s_mlx->mlx, WIDTH, HEIGHT, s_mlx->name);
	if (!s_mlx->mlx_win)
	{
		mlx_destroy_display(s_mlx->mlx);
		free(s_mlx->mlx);
		free(elem);
		exit(EXIT_FAILURE);
	}
	s_mlx->img.img = mlx_new_image(s_mlx->mlx, WIDTH, HEIGHT);
	if (!s_mlx->img.img)
	{
		mlx_destroy_window(s_mlx->mlx, s_mlx->mlx_win);
		mlx_destroy_display(s_mlx->mlx);
		free(s_mlx->mlx);
		free(elem);
		exit(EXIT_FAILURE);
	}
	s_mlx->img.addr = mlx_get_data_addr(s_mlx->img.img,
			&s_mlx->img.bits_per_pixel, &s_mlx->img.line_length,
			&s_mlx->img.endian);
}

int	esc(t_data *data)
{
	mlx_destroy_image(data->mlx_struct->mlx, data->mlx_struct->img.img);
	mlx_destroy_window(data->mlx_struct->mlx, data->mlx_struct->mlx_win);
	mlx_destroy_display(data->mlx_struct->mlx);
	free(data->mlx_struct->mlx);
	free(data->elem);
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
	while (elem)
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

void	build_ray(t_data *data, t_point pixel_camera)
{
	t_point		origin;
	t_vector	direction;
	t_elem		camera;

	camera = *get_type_element(data->elem, C);
	origin = (t_point){0, 0, 0};
	direction = normalize(two_points_vect(origin, pixel_camera));
	origin = axes_sum(origin, camera.pos);
	direction = rotate_vector(direction, camera.orientation);
	printf("origin: %f %f %f\n", origin.x, origin.y, origin.z);
	printf("direction: %f %f %f\n", direction.x, direction.y, direction.z);
	printf("\n");
	printf("\n");
}

void	build_image(t_data *data)
{
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
				* WIDTH / (double)HEIGHT * tan(data->elem->fov / 2.0);
			pixel_camera_y = (1 - 2 * (2 * (y + 0.5) / HEIGHT - 1))
				* tan(data->elem->fov / 2.0);
			printf("pixel_camera_x: %f\n", pixel_camera_x);
			printf("pixel_camera_y: %f\n", pixel_camera_y);
			printf("\n");
			printf("\n");
			//build_ray(data, (t_point){pixel_camera_x, pixel_camera_y, 1});
			x++;
		}
		y++;
	}
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
	data.elem = elem;
	data.mlx_struct = &mlx_struct;
	build_image(&data);
	mlx_hook(mlx_struct.mlx_win, 2, 1L << 0, key_down, &data);
	mlx_hook(mlx_struct.mlx_win, 17, 0L, esc, &data);
	mlx_loop(mlx_struct.mlx);
	return (0);
}
