/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:31:36 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/29 13:36:29 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* The distance represented by a vector is the length of the vector or the
magnitude of the vector. */

double	magnitude(t_tuple v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/* Normalizing a vector is the process of turning a vector into a unit vector.
Which is a vector with a magnitude of 1. */

t_tuple	normalize(t_tuple v)
{
	double mag;
	t_tuple norm;

	mag = magnitude(v);
	norm.x = v.x / mag;
	norm.y = v.y / mag;
	norm.z = v.z / mag;
	norm.w = v.w / mag;
	return (norm);
}

/* The dot product of two vectors is a scalar value. We will use it to compute
shading on a surface and intersection of rays with objects. */

double	dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

/* The cross product of two vectors is a vector. It returns a new vector that is
perpendicular to the two input vectors. */

t_tuple	cross(t_tuple a, t_tuple b)
{
	t_tuple cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	cross.w = 0.0;
	return (cross);
}
