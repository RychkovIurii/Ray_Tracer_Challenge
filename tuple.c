/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:07:36 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/15 18:28:54 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

int equal(t_tuple a, t_tuple b)
{
	if (fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON &&
		fabs(a.z - b.z) < EPSILON && fabs(a.w - b.w) < EPSILON)
		return (1);
	return (0);
}

int is_point(t_tuple a)
{
	return (a.w == 1.0);
}

int is_vector(t_tuple a)
{
	return (a.w == 0.0);
}
