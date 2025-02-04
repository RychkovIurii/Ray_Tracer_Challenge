/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:46:44 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 15:43:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Translation matrix. */

t_matrix4x4	*translation_matrix(double x, double y, double z)
{
	t_matrix4x4	result;

	result[0][0] = 1;
	result[1][1] = 1;
	result[2][2] = 1;
	result[3][3] = 1;
	result[0][3] = x;
	result[1][3] = y;
	result[2][3] = z;
	return (result);
}

/* Scaling matrix. */

t_matrix4x4	*scaling_matrix(double x, double y, double z)
{
	t_matrix4x4	result;

	ft_bzero(&result, sizeof(t_matrix4x4));
	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = z;
	result[3][3] = 1;
	return (result);
}

/* Rotation matrix. */

t_matrix4x4	*rotation_x_matrix(double radian)
{
	t_matrix4x4	result;

	ft_bzero(&result, sizeof(t_matrix4x4));
	result[0][0] = 1;
	result[1][1] = cos(radian);
	result[1][2] = -sin(radian);
	result[2][1] = sin(radian);
	result[2][2] = cos(radian);
	result[3][3] = 1;
	return (result);
}

t_matrix4x4	*rotation_y_matrix(double radian)
{
	t_matrix4x4	result;

	ft_bzero(&result, sizeof(t_matrix4x4));
	result[0][0] = cos(radian);
	result[0][2] = sin(radian);
	result[1][1] = 1;
	result[2][0] = -sin(radian);
	result[2][2] = cos(radian);
	result[3][3] = 1;
	return (result);
}

t_matrix4x4	*rotation_z_matrix(double radian)
{
	t_matrix4x4	result;

	ft_bzero(&result, sizeof(t_matrix4x4));
	result[0][0] = cos(radian);
	result[0][1] = -sin(radian);
	result[1][0] = sin(radian);
	result[1][1] = cos(radian);
	result[2][2] = 1;
	result[3][3] = 1;
	return (result);
}

/* Shearing matrix. */

t_matrix4x4	*shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy)
{
	t_matrix4x4	result;

	ft_bzero(&result, sizeof(t_matrix4x4));
	result[0][0] = 1;
	result[0][1] = xy;
	result[0][2] = xz;
	result[1][0] = yx;
	result[1][1] = 1;
	result[1][2] = yz;
	result[2][0] = zx;
	result[2][1] = zy;
	result[2][2] = 1;
	result[3][3] = 1;
	return (result);
}
