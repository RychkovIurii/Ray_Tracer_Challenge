/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:32:10 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/03 19:23:11 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward = normalize(substract_tuple(to, from));
	t_tuple upn = normalize(up);
	t_tuple left = cross(forward, upn);
	t_tuple true_up = cross(left, forward);

	t_matrix orientation = create_matrix(4);
	orientation.matrix[0][0] = left.x;
	orientation.matrix[0][1] = left.y;
	orientation.matrix[0][2] = left.z;
	orientation.matrix[0][3] = 0;
	orientation.matrix[1][0] = true_up.x;
	orientation.matrix[1][1] = true_up.y;
	orientation.matrix[1][2] = true_up.z;
	orientation.matrix[1][3] = 0;
	orientation.matrix[2][0] = -forward.x;
	orientation.matrix[2][1] = -forward.y;
	orientation.matrix[2][2] = -forward.z;
	orientation.matrix[2][3] = 0;
	orientation.matrix[3][0] = 0;
	orientation.matrix[3][1] = 0;
	orientation.matrix[3][2] = 0;
	orientation.matrix[3][3] = 1;

	t_matrix translation = translation_matrix(-from.x, -from.y, -from.z);
	return multiply_matrices(orientation, translation);
}
