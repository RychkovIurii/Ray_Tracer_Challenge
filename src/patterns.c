/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:47 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/07 15:49:52 by irychkov         ###   ########.fr       */
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

t_pattern		gradient_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix(4);
	return (pattern);
}

t_tuple		gradient_at(t_pattern pattern, t_tuple point)
{
	t_tuple distance;
	double fraction;

	distance = substract_tuple(pattern.color_b, pattern.color_a);
	fraction = point.x - floor(point.x);
	return (add_tuple(pattern.color_a, multiply_tuple_scalar(distance, fraction)));
}

t_pattern		ring_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix(4);
	return (pattern);
}

t_tuple		ring_at(t_pattern pattern, t_tuple point)
{
	int floored_distance = (int)floor(sqrt(point.x * point.x + point.z * point.z));
	if (floored_distance % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_pattern		checker_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
	pattern.transform = identity_matrix(4);
	return (pattern);
}

t_tuple		checker_at(t_pattern pattern, t_tuple point)
{
	int floored_sum = (int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z);
	if (floored_sum % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

t_tuple pattern_at_object(t_pattern pattern, t_shape shape, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple pattern_point;

	object_point = multiply_matrix_by_tuple(inverse_matrix(shape.transform), world_point);
	pattern_point = multiply_matrix_by_tuple(inverse_matrix(pattern.transform), object_point);

	if (shape.material.has_pattern == PATTERN_STRIPE)
		return (stripe_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_GRADIENT)
		return (gradient_at(pattern, pattern_point));
	else if (shape.material.has_pattern == PATTERN_RING)
		return (ring_at(pattern, pattern_point));
	else
		return (checker_at(pattern, pattern_point));
}
