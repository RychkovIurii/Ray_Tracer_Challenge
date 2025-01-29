/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:14:51 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/29 13:36:11 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_tuple	create_tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}

t_tuple	point(double x, double y, double z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 1.0;
	return (tuple);
}

t_tuple	vector(double x, double y, double z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = 0.0;
	return (tuple);
}

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x + b.x;
	tuple.y = a.y + b.y;
	tuple.z = a.z + b.z;
	tuple.w = a.w + b.w;
	return (tuple);
}

t_tuple	substract_tuple(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x - b.x;
	tuple.y = a.y - b.y;
	tuple.z = a.z - b.z;
	tuple.w = a.w - b.w;
	return (tuple);
}

t_tuple	negate_tuple(t_tuple a)
{
	t_tuple	tuple;

	tuple.x = -a.x;
	tuple.y = -a.y;
	tuple.z = -a.z;
	tuple.w = -a.w;
	return (tuple);
}

t_tuple	multiply_tuple_scalar(t_tuple a, double scalar)
{
	t_tuple	tuple;

	tuple.x = a.x * scalar;
	tuple.y = a.y * scalar;
	tuple.z = a.z * scalar;
	tuple.w = a.w * scalar;
	return (tuple);
}

t_tuple	divide_tuple(t_tuple a, double scalar)
{
	t_tuple	tuple;

	tuple.x = a.x / scalar;
	tuple.y = a.y / scalar;
	tuple.z = a.z / scalar;
	tuple.w = a.w / scalar;
	return (tuple);
}
