/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:02:55 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 15:42:54 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Function to create a point light source.
** @param position: The position(point) of the light source.
** @param intensity: The intensity(color) of the light source.
** @return The struct of the light source.
*/
t_light		point_light(t_tuple position, t_tuple intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}
