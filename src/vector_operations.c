/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:31:36 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 12:13:04 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* The distance represented by a vector is the length of the vector or the
magnitude of the vector.
@param vector to calculate the magnitude of.
@returns the square root of the sum of the squares of the vector's components. */
double	magnitude(t_tuple v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/* Normalizing a vector is the process of turning a vector into a unit vector.
Which is a vector with a magnitude of 1.
@param vector to normalize.
@returns a new vector that is the normalized version of the input vector. */
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
shading on a surface and intersection of rays with objects.
@param two vectors to calculate the dot product of.
@returns a scalar value. */
double	dot(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

/* The cross product of two vectors is a vector. It returns a new vector that is
perpendicular to the two input vectors.
@param two vectors to calculate the cross product of.
@returns a new vector that is perpendicular to the two input vectors. */
t_tuple	cross(t_tuple a, t_tuple b)
{
	t_tuple cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	cross.w = 0.0;
	return (cross);
}

/*
** Reflect function calculates the reflection vector of the incoming vector
** in relation to the normal vector of the surface it hits.
** The formula is R = V - 2 * N * dot(V, N)
** where V is the incoming vector, N is the normal vector of the surface
** and R is the reflection vector.
** @param in: The incoming vector.
** @param normal: The normal vector of the surface.
** @return The reflection vector.
*/
t_tuple reflect(t_tuple in, t_tuple normal)
{
	t_tuple result;
	t_tuple n;
	t_tuple n2;
	t_tuple n3;

	n = multiply_tuple_scalar(normal, 2);
	n2 = multiply_tuple_scalar(n, dot(in, normal));
	n3 = substract_tuple(in, n2);
	result = n3;
	return (result);
}
