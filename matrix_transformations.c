/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/17 12:01:35 by irychkov         ###   ########.fr       */
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

/* Scaling matrix. */

t_matrix	scaling_matrix(double x, double y, double z)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = x;
	result.matrix[1][1] = y;
	result.matrix[2][2] = z;
	result.matrix[3][3] = 1;
	return (result);
}

/* Rotation matrix. */

t_matrix	rotation_x_matrix(double radian)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = 1;
	result.matrix[1][1] = cos(radian);
	result.matrix[1][2] = -sin(radian);
	result.matrix[2][1] = sin(radian);
	result.matrix[2][2] = cos(radian);
	result.matrix[3][3] = 1;
	return (result);
}

t_matrix	rotation_y_matrix(double radian)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = cos(radian);
	result.matrix[0][2] = sin(radian);
	result.matrix[1][1] = 1;
	result.matrix[2][0] = -sin(radian);
	result.matrix[2][2] = cos(radian);
	result.matrix[3][3] = 1;
	return (result);
}

t_matrix	rotation_z_matrix(double radian)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = cos(radian);
	result.matrix[0][1] = -sin(radian);
	result.matrix[1][0] = sin(radian);
	result.matrix[1][1] = cos(radian);
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	return (result);
}
