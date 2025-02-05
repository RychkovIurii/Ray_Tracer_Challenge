/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:20:04 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 15:20:09 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
