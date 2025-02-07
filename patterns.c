/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:47 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/07 12:47:06 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_pattern		stripe_pattern(t_tuple a, t_tuple b)
{
	t_pattern	pattern;

	pattern.color_a = a;
	pattern.color_b = b;
/* 	pattern.transform = identity_matrix(4); */
	return (pattern);
}

t_tuple	stripe_at(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (pattern.color_a);
	else
		return (pattern.color_b);
}