/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:47 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/07 14:40:52 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void set_pattern_transform(t_pattern *pattern, t_matrix transform)
{
	pattern->transform = transform;
}

t_pattern		stripe_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix(4);
	return (pattern);
}

t_tuple	stripe_at(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_tuple stripe_at_object(t_pattern pattern, t_shape shape, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple pattern_point;

	object_point = multiply_matrix_by_tuple(inverse_matrix(shape.transform), world_point);
	pattern_point = multiply_matrix_by_tuple(inverse_matrix(pattern.transform), object_point);

	return (stripe_at(pattern, pattern_point));
}

#include <assert.h>

int is_identity_matrix(t_matrix m)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if ((i == j && m.matrix[i][j] != 1) || (i != j && m.matrix[i][j] != 0))
				return (0);
	return (1);
}

void test_set_pattern_transform()
{
	t_pattern pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));
	assert(is_identity_matrix(pattern.transform));
}

t_tuple another_stripe_at(t_pattern pattern, t_tuple point)
{
	return create_color(point.x, point.y, point.z);
}

t_tuple another_stripe_at_object(t_pattern pattern, t_shape shape, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple pattern_point;

	object_point = multiply_matrix_by_tuple(inverse_matrix(shape.transform), world_point);
	pattern_point = multiply_matrix_by_tuple(inverse_matrix(pattern.transform), object_point);

	return (another_stripe_at(pattern, pattern_point));
}

void test_pattern_with_object_transform()
{
	t_shape shape = create_shape(SHAPE_SPHERE);
	shape.material.has_pattern = 1;
	shape.transform = scaling_matrix(2, 2, 2);
	t_pattern pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));

	t_tuple c = another_stripe_at_object(pattern, shape, point(2, 3, 4));
	assert(c.x == 1);
	assert(c.y == 1.5);
	assert(c.z == 2);
}



void test_pattern_with_both_transforms()
{
	t_shape shape = create_shape(SHAPE_SPHERE);
	shape.transform = scaling_matrix(2, 2, 2);

	t_pattern pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));
	set_pattern_transform(&pattern, translation_matrix(0.5, 1, 1.5));

	t_tuple c = another_stripe_at_object(pattern, shape, point(2.5, 3, 3.5));
	assert(c.x == 0.75);
	assert(c.y == 0.5);
	assert(c.z == 0.25);
}

int main()
{
	test_set_pattern_transform();
	test_pattern_with_object_transform();
	test_pattern_with_both_transforms();
	printf("All tests passed!\n");
	return (0);
}