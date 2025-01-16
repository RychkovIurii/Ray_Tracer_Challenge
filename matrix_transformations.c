/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/16 16:08:51 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

/* Translation matrix. */

t_matrix	translation_matrix(double x, double y, double z)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = 1;
	result.matrix[1][1] = 1;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	result.matrix[0][3] = x;
	result.matrix[1][3] = y;
	result.matrix[2][3] = z;
	return (result);
}
