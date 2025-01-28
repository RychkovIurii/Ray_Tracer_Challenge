/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/28 18:09:58 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "rays.h"
#include "matrix.h"

t_ray			create_ray(t_tuple origin, t_tuple direction)
{
	t_ray		result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_tuple			get_ray_position(t_ray ray, double t)
{
	t_tuple		result;

	result = add_tuple(ray.origin, multiply_tuple_scalar(ray.direction, t));
	return (result);
}


/* t_intersection create_intersection(double t, t_object *object)
{
	t_intersection result;

	result.t = t;
	result.object = object;
	return (result);
} */

/*
	Function reurns the number of intersections between the ray and the sphere
	and the values of t at which the intersections occur.
	Lowest value of t is a hit closest to the ray's origin.
	We need all values for reflections and refractions.
*/
t_intersects	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_intersects result;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_intersection	intersection1;
	t_intersection	intersection2;

	sphere_to_ray = substract_tuple(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
/* 	printf("a: %f, b: %f, c: %f, discriminant: %f\n", a, b, c, discriminant); */
	if (discriminant < 0)
	{
		result.count = 0;
		result.array = NULL;
		return (result);
	}
	intersection1.t = (-b - sqrt(discriminant)) / (2 * a);
	intersection1.object = &sphere;
	intersection2.t = (-b + sqrt(discriminant)) / (2 * a);
	intersection2.object = &sphere;
	result.count = 2;
	result.array = (t_intersection *)malloc(sizeof(t_intersection) * 2);
	result.array[0] = intersection1;
	result.array[1] = intersection2;
	return (result);
}

/*
	Function returns the intersection of the ray with the object.
	Lowest value of t is a hit closest to the ray's origin.
*/

t_intersection	*hit(t_intersects intersections)
{
	t_intersection	*hit;
	int				i;

	hit = NULL;
	i = 0;

	while (i < intersections.count)
	{
		if (intersections.array[i].t > 0)
		{
			if (hit == NULL)
				hit = &intersections.array[i];
			else if (intersections.array[i].t < hit->t)
				hit = &intersections.array[i];
		}
		i++;
	}
	return (hit);
}

t_ray	transform_ray(t_ray ray, t_matrix matrix)
{
	t_ray		result;

	result.origin = multiply_matrix_by_tuple(matrix, ray.origin);
	result.direction = multiply_matrix_by_tuple(matrix, ray.direction);
	return (result);
}

/* #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

void test_intersection_no_hit()

{
	t_ray ray = {{0, 0, 0, 1}, {1, 0, 0, 0}};
	t_sphere sphere = {{0, 5, 0, 1}, 1};
	t_intersects result = intersect_sphere(ray, sphere);

	assert(result.count == 0);
	assert(result.array == NULL);
}

void test_intersection_two_hits()
{
	t_ray ray = {{0, 0, 0, 1}, {1, 0, 0, 0}};
	t_sphere sphere = {{5, 0, 0, 1}, 1};
	t_intersects result = intersect_sphere(ray, sphere);

	assert(result.count == 2);
	assert(result.array != NULL);
	assert(fabs(result.array[0].t - 4.0) < 1e-6);
	assert(fabs(result.array[1].t - 6.0) < 1e-6);
	free(result.array);
}

void test_hit_no_intersections()
{
	t_intersects intersections = {0, NULL};
	t_intersection *result = hit(intersections);

	assert(result == NULL);
}

void test_hit_closest_intersection()
{
	t_intersection intersections_array[3] = {
		{5, NULL},
		{3, NULL},
		{7, NULL}
	};
	t_intersects intersections = {3, intersections_array};
	t_intersection *result = hit(intersections);

	assert(result != NULL);
	assert(result->t == 3);
}

void test_transform_ray()
{
	t_ray ray = create_ray(create_tuple(1, 2, 3, 1), create_tuple(0, 1, 0, 0));
	t_matrix tran_matrix = translation_matrix(3, 4, 5);
	t_ray transformed_ray = transform_ray(ray, tran_matrix);
	assert(is_tuples_equal(transformed_ray.origin, create_tuple(4, 6, 8, 1)));
	assert(is_tuples_equal(transformed_ray.direction, create_tuple(0, 1, 0, 0)));

	t_matrix scal_matrix = scaling_matrix(2, 3, 4);
	transformed_ray = transform_ray(ray, scal_matrix);
	assert(is_tuples_equal(transformed_ray.origin, create_tuple(2, 6, 12, 1)));
	assert(is_tuples_equal(transformed_ray.direction, create_tuple(0, 3, 0, 0)));
}

int main()
{
	test_intersection_no_hit();
	test_intersection_two_hits();
	test_hit_no_intersections();
	test_hit_closest_intersection();
	test_transform_ray();

	printf("All tests passed!\n");
	return 0;
} */