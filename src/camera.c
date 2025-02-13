/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:09:13 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/11 12:22:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	camera;
	double		half_view;
	double		aspect;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.field_of_view = field_of_view;
	camera.transform = identity_matrix(4);
	//printf("Camera matrix:\n");
	//print_matrix(camera.transform);

	half_view = tan(camera.field_of_view / 2);
	aspect = (double)camera.hsize / (double)camera.vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / camera.hsize;

	return (camera);
}

t_ray ray_for_pixel(t_camera camera, int px, int py)
{
	double xoffset = (px + 0.5) * camera.pixel_size;
	double yoffset = (py + 0.5) * camera.pixel_size;

	double world_x = camera.half_width - xoffset;
	double world_y = camera.half_height - yoffset;

	t_tuple pixel = multiply_matrix_by_tuple(inverse_matrix(camera.transform), point(world_x, world_y, -1));
	//printf("Pixel: %f %f %f\n", pixel.x, pixel.y, pixel.z);
	t_tuple origin = multiply_matrix_by_tuple(inverse_matrix(camera.transform), point(0, 0, 0));
	//printf("Origin: %f %f %f\n", origin.x, origin.y, origin.z);
	t_tuple direction = normalize(substract_tuple(pixel, origin));

	return create_ray(origin, direction);
}

t_canvas *render(t_camera camera, t_world *world)
{
	t_canvas *image = create_canvas(camera.hsize, camera.vsize);
	//printf("Camera matrix inside render:\n");
	//print_matrix(camera.transform);
	for (int y = 0; y < camera.vsize; y++)
	{
		for (int x = 0; x < camera.hsize; x++)
		{
			t_ray ray = ray_for_pixel(camera, x, y);
			t_tuple color = color_at(world, ray, DEFAULT_REMAINING);
			write_pixel(image, x, y, color);
		}
	}
	return (image);
}
