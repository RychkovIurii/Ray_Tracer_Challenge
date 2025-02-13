/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/10 23:24:59 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

	if (x == 0 || y == 0 || z == 0)
    {
        printf("Error: Scaling matrix has a zero component and is not invertible!\n");
        exit(1);
    }
	result = identity_matrix(4);
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

/* Shearing matrix. */

t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_matrix	result;

	result = create_matrix(4);
	result.matrix[0][0] = 1;
	result.matrix[0][1] = xy;
	result.matrix[0][2] = xz;
	result.matrix[1][0] = yx;
	result.matrix[1][1] = 1;
	result.matrix[1][2] = yz;
	result.matrix[2][0] = zx;
	result.matrix[2][1] = zy;
	result.matrix[2][2] = 1;
	result.matrix[3][3] = 1;
	return (result);
}
