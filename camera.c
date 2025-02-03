/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:09:13 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/03 19:23:33 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_matrix	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
}				t_camera;

t_camera create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	camera;
	double		half_view;
	double		aspect;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.field_of_view = field_of_view;
	camera.transform = identity_matrix(4);

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


/* #include <assert.h>

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

int main()
{
	test_pixel_size_horizontal_canvas();
	test_pixel_size_vertical_canvas();
	return 0;
} */
