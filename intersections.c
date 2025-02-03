/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:42:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/03 16:08:25 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n > 0)
	{
		*temp = 0;
		n--;
		temp++;
	}
}

t_intersection prepare_computations(t_intersection hit, t_ray ray)
{
	t_intersection comps;

	ft_bzero(&comps, sizeof(t_intersection));
	comps.t = hit.t;
	if (!comps.t)
		return (comps);
	comps.object = hit.object;
	comps.point = get_ray_position(ray, hit.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(*hit.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = 0;
	return (comps);
}
