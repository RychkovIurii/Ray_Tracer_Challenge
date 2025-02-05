/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_spheres.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:01:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 15:01:24 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* int main()
{
	t_world w = default_world();
	t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersects xs = intersect_world(w, r);
	t_intersection *hits = hit(xs);
	if (hits != NULL && hits->t == 4)
		printf("Test passed\n Hit point: %f\n", hits->t);
	else
		printf("Test failed\n Hit point: %f\n", hits->t);
	free(xs.array);
	free(w.sphere[0]);
	free(w.sphere[1]);
	free(w.sphere);
	return (0);
}
 */
/* 
#include <assert.h>

void	free_world(t_world *world)
{
	free(world->sphere[0]);
	free(world->sphere[1]);
	free(world->sphere);
}

void test_color_when_ray_misses()
{
	t_world world = default_world();
	t_ray ray = create_ray(point(0, 0, -5), vector(0, 1, 0));

	t_tuple color = color_at(world, ray);

	assert(is_tuples_equal(color, create_color(0, 0, 0)));

	free_world(&world);
	printf("Test_color_when_ray_misses passed\n");
}

void test_color_when_ray_hits()
{
	t_world world = default_world();
	t_ray ray = create_ray(point(0, 0, -5), vector(0, 0, 1));

	t_tuple color = color_at(world, ray);

	t_tuple expected_color = create_color(0.38066, 0.47583, 0.2855);
	assert(is_tuples_equal(color, expected_color));

	free_world(&world);
	printf("Test_color_when_ray_hits passed\n");
}

void test_color_with_intersection_behind_ray()
{
	t_world world = default_world();
	t_sphere *outer = world.sphere[0];
	t_sphere *inner = world.sphere[1];

	outer->material.ambient = 1;
	inner->material.ambient = 1;

	t_ray ray = create_ray(point(0, 0, 0.75), vector(0, 0, -1));

	t_tuple color = color_at(world, ray);

	assert(is_tuples_equal(color, inner->material.color));

	free_world(&world);
	printf("Test_color_with_intersection_behind_ray passed\n");
}

int main()
{
	test_color_when_ray_misses();
	//test_color_when_ray_hits();
	test_color_with_intersection_behind_ray();
	printf("All tests passed!\n");
	return 0;
}
 */
