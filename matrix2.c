/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 14:44:48 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Submatrix returns a copy of the given matrix with the given row and column removed. */
t_matrix	submatrix(t_matrix a, int row, int column)
{
	t_matrix	sub;
	int		i;
	int		j;
	int		x;
	int		y;

	if (a.size < 2)
	{
		printf("Error: Matrix is too small\n"); // Handle error: matrix is too small
		return (a);
	}
	sub = create_matrix(a.size - 1);
	x = 0;
	i = 0;
	while (i < a.size)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		y = 0;
		while (j < a.size)
		{
			if (j == column)
			{
				j++;
				continue;
			}
			sub.matrix[x][y] = a.matrix[i][j];
			y++;
			j++;
		}
		x++;
		i++;
	}
	return (sub);
}

/* Calculate the minor of matrix. */
double	minor_matrix(t_matrix a, int row, int column)
{
	t_matrix	sub;
	double	det;

	sub = submatrix(a, row, column);
	det = determinant(sub);
	free_matrix(sub);
	return (det);
}


/* Calculate the cofactor of a 3x3 matrix. */
double	cofactor_matrix(t_matrix a, int row, int column)
{
	double	minor;
	double	cofactor;

	minor = minor_matrix(a, row, column);
	if ((row + column) % 2 == 0)
		cofactor = minor;
	else
		cofactor = -minor;
	return (cofactor);
}

/* Calculate the determinant of a matrix. */
double	determinant(t_matrix a)
{
	double	det;
	int		i;

	i = 0;
	det = 0;
	if (a.size == 2)
		return (a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0]);
	while (i < a.size)
	{
		det += a.matrix[0][i] * cofactor_matrix(a, 0, i);
		i++;
	}
	return (det);
}

/* Is matrix invertible */
int		is_invertible(t_matrix a)
{
	if (determinant(a) == 0)
		return (0);
	return (1);
}

/* Inverse matrix. */
t_matrix	inverse_matrix(t_matrix a)
{
	t_matrix	inverse;
	double		det;
	int			i;
	int			j;

	if (a.matrix == NULL)
	{
		printf("Error: Received NULL matrix\n");
		exit(1); // Handle error, potentially return an invalid matrix
	}
	det = determinant(a);
	if (det == 0)
	{
		printf("Matrix is not invertible\n");
		//print_matrix(a);
		return (identity_matrix(4));
	}
	inverse = create_matrix(a.size);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			inverse.matrix[j][i] = cofactor_matrix(a, i, j) / det;
			j++;
		}
		i++;
	}
	return (inverse);
}
