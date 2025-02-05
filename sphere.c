/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:01:59 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 14:12:27 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

/*
** Function that takes a point and a sphere and returns the normal vector of the sphere at that point.
** @param sphere: The sphere.
** @param world_point: The point in the world.
** @return The normal vector of the sphere at that point.
*/
t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
{
	t_tuple surface_normal;
	t_tuple world_normal;
	t_tuple object_point;
	t_tuple object_normal;
	t_matrix inverse_transform;

	inverse_transform = inverse_matrix(sphere.transform);
	object_point = multiply_matrix_by_tuple(inverse_transform, world_point);
	object_normal = substract_tuple(object_point, sphere.center);
	world_normal = multiply_matrix_by_tuple(transpose_matrix(inverse_transform), object_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}

/* 
#include <assert.h>

t_matrix identity_matrix(int size) {
	t_matrix m;

	m.size = size;
	m.matrix = (double **)malloc(size * sizeof(double *));
	for (int i = 0; i < size; i++) {
		m.matrix[i] = (double *)malloc(size * sizeof(double));
		for (int j = 0; j < size; j++) {
			if (i == j)
				m.matrix[i][j] = 1;
			else
				m.matrix[i][j] = 0;
		}
	}
	return (m);
}

void test_normal_at()
{
	t_sphere sphere = { point(0, 0, 0), 1, identity_matrix(4) };
	t_tuple expected, actual;

	// Normal at point on X-axis
	expected = vector(1, 0, 0);
	actual = normal_at(sphere, point(1, 0, 0));
	assert(is_tuples_equal(expected, actual));

	// Normal at point on Y-axis
	expected = vector(0, 1, 0);
	actual = normal_at(sphere, point(0, 1, 0));
	assert(is_tuples_equal(expected, actual));

	// Normal at point on Z-axis
	expected = vector(0, 0, 1);
	actual = normal_at(sphere, point(0, 0, 1));
	assert(is_tuples_equal(expected, actual));

	// Normal at non-axial point
	expected = normalize(vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	actual = normal_at(sphere, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
	assert(is_tuples_equal(expected, actual));

	printf("All normal_at() tests passed!\n");
}

void test_reflect()
{
	t_tuple v, normal, expected, actual;

	// Reflection at 45-degree angle
	v = vector(1, -1, 0);
	normal = vector(0, 1, 0);
	expected = vector(1, 1, 0);
	actual = reflect(v, normal);
	assert(is_tuples_equal(expected, actual));

	// Reflection at another angle
	v = vector(0, -1, 0);
	normal = vector(sqrt(2)/2, sqrt(2)/2, 0);
	expected = vector(1, 0, 0);
	actual = reflect(v, normal);
	assert(is_tuples_equal(expected, actual));

	printf("All reflect() tests passed!\n");
}

int main()
{
	test_normal_at();
	test_reflect();
	return 0;
}
 */