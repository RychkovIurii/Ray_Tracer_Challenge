/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:32:10 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 16:42:12 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix4x4 *view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward = normalize(substract_tuple(to, from));
	t_tuple upn = normalize(up);
	t_tuple left = cross(forward, upn);
	t_tuple true_up = cross(left, forward);

	t_matrix4x4 *orientation;
	*orientation[0][0] = left.x;
	*orientation[0][1] = left.y;
	*orientation[0][2] = left.z;
	*orientation[0][3] = 0;
	*orientation[1][0] = true_up.x;
	*orientation[1][1] = true_up.y;
	*orientation[1][2] = true_up.z;
	*orientation[1][3] = 0;
	*orientation[2][0] = -forward.x;
	*orientation[2][1] = -forward.y;
	*orientation[2][2] = -forward.z;
	*orientation[2][3] = 0;
	*orientation[3][0] = 0;
	*orientation[3][1] = 0;
	*orientation[3][2] = 0;
	*orientation[3][3] = 1;

	t_matrix4x4 *translation;
	ft_bzero(&translation, sizeof(t_matrix4x4));
	translation = translation_matrix(-from.x, -from.y, -from.z);
	t_matrix4x4 *result;
	ft_bzero(&result, sizeof(t_matrix4x4 *));
	result = multiply_matrices(orientation, translation);
	return (result);
}
