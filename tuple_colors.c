/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:06:59 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/14 15:21:51 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	color(double r, double g, double b)
{
	t_tuple	tuple;

	tuple.x = r;
	tuple.y = g;
	tuple.z = b;
	tuple.w = 0.0; // Think do we need a flag for color?
	return (tuple);
}

/* Hadamard product is a term for element-wise multiplication of two tuples.
We can call it a "multiply_color" as well. */

t_tuple	hadamard_product(t_tuple a, t_tuple b)
{
	t_tuple	tuple;

	tuple.x = a.x * b.x;
	tuple.y = a.y * b.y;
	tuple.z = a.z * b.z;
	tuple.w = a.w * b.w; // Think what to do with the flag.
	return (tuple);
}
