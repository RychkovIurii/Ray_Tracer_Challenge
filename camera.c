/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera->c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:09:13 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 14:12:05 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_camera *create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	*camera;
	double		half_view;
	double		aspect;

	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->field_of_view = field_of_view;
	set_identity_matrix(camera->transform, 4);

	half_view = tan(camera->field_of_view / 2);
	aspect = (double)camera->hsize / (double)camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;

	return (camera);
}

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
	t_tuple pixel;
	t_tuple origin;
	t_tuple direction;
	t_matrix4x4 inverse;

	ft_bzero(&pixel, sizeof(t_tuple));
	ft_bzero(&origin, sizeof(t_tuple));
	ft_bzero(&direction, sizeof(t_tuple));
	double xoffset = (px + 0.5) * camera->pixel_size;
	double yoffset = (py + 0.5) * camera->pixel_size;

	double world_x = camera->half_width - xoffset;
	double world_y = camera->half_height - yoffset;

	inverse_matrix(&inverse, camera->transform);
	pixel = multiply_matrix_by_tuple(inverse, point(world_x, world_y, -1));
	origin = multiply_matrix_by_tuple(inverse, point(0, 0, 0));
	direction = normalize(substract_tuple(pixel, origin));

	return create_ray(origin, direction);
}

t_canvas *render(t_camera *camera, t_world world)
{
	t_canvas *image;
	t_ray ray;
	t_tuple color;

	ft_bzero(&image, sizeof(t_canvas *));
	ft_bzero(&ray, sizeof(t_ray));
	ft_bzero(&color, sizeof(t_tuple));
	image = create_canvas(camera->hsize, camera->vsize);
	for (int y = 0; y < camera->vsize; y++)
	{
		for (int x = 0; x < camera->hsize; x++)
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(world, ray);
			write_pixel(image, x, y, color);
		}
	}
	return (image);
}

/* 
#include <assert.h>

void test_pixel_size_horizontal_canvas()
{
	t_camera c = create_camera(200, 125, M_PI / 2);
	assert(fabs(c.pixel_size - 0.01) < 1e-6);
	printf("test_pixel_size_horizontal_canvas passed\n");
}

void test_pixel_size_vertical_canvas()
{
	t_camera c = create_camera(125, 200, M_PI / 2);
	assert(fabs(c.pixel_size - 0.01) < 1e-6);
	printf("test_pixel_size_vertical_canvas passed\n");
}

void test_ray_for_pixel_center()
{
	t_camera c = create_camera(201, 101, M_PI / 2);
	t_ray r = ray_for_pixel(c, 100, 50);
	assert(is_tuples_equal(r.origin, point(0, 0, 0)));
	assert(is_tuples_equal(r.direction, vector(0, 0, -1)));
	printf("test_ray_for_pixel_center passed\n");
}

void test_ray_for_pixel_corner()
{
	t_camera c = create_camera(201, 101, M_PI / 2);
	t_ray r = ray_for_pixel(c, 0, 0);
	assert(is_tuples_equal(r.origin, point(0, 0, 0)));
	assert(is_tuples_equal(r.direction, vector(0.66519, 0.33259, -0.66851)));
	printf("test_ray_for_pixel_corner passed\n");
}

void test_ray_for_pixel_transformed()
{
	t_camera c = create_camera(201, 101, M_PI / 2);
	c.transform = multiply_matrices(rotation_y_matrix(M_PI / 4), translation_matrix(0, -2, 5));
	t_ray r = ray_for_pixel(c, 100, 50);
	assert(is_tuples_equal(r.origin, point(0, 2, -5)));
	assert(is_tuples_equal(r.direction, vector(sqrt(2)/2, 0, -sqrt(2)/2)));
	printf("test_ray_for_pixel_transformed passed\n");
}

int main()
{
	test_pixel_size_horizontal_canvas();
	test_pixel_size_vertical_canvas();
	test_ray_for_pixel_center();
	test_ray_for_pixel_corner();
	test_ray_for_pixel_transformed();
	return 0;
}
 */
