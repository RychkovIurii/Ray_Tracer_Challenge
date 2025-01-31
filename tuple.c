/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:07:36 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 12:50:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Functions to validate tuples.
@param a, b: tuples to compare.
@returns 1 if the tuples are equal, 0 otherwise. */
int	is_tuples_equal(t_tuple a, t_tuple b)
{
	if (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON &&
		fabs(a.z - b.z) < EPSILON && fabs(a.w - b.w) < EPSILON)
		return (1);
	return (0);
}

/*Validatates if the tuple is a point.
@param a: tuple to validate.
@returns 1 if the tuple is a point, 0 otherwise. */
int	is_point(t_tuple a)
{
	return (a.w == 1.0);
}

/*Validatates if the tuple is a vector.
@param a: tuple to validate.
@returns 1 if the tuple is a vector, 0 otherwise. */
int	is_vector(t_tuple a)
{
	return (a.w == 0.0);
}
