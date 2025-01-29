/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:01:59 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/29 16:15:31 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

/*
** Sphere is a struct that holds the center of the sphere, its radius, and the
** transformation matrix.
** @return The surface normal vector.
*/
t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
{
	t_tuple surface_normal;
	t_tuple world_normal;
	t_tuple object_point;
	t_tuple object_normal;

	object_point = multiply_matrix_by_tuple(inverse_matrix(sphere.transform), world_point);
	object_normal = substract_tuple(object_point, point(0, 0, 0));
	world_normal = multiply_matrix_by_tuple(transpose_matrix(inverse_matrix(sphere.transform)), object_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}

/*
** Reflect function calculates the reflection vector of the incoming vector
** in relation to the normal vector of the surface it hits.
** The formula is R = V - 2 * N * dot(V, N)
** where V is the incoming vector, N is the normal vector of the surface
** and R is the reflection vector.
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


