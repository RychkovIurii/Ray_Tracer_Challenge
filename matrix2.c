/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/16 11:58:17 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

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
		// Handle error: matrix is too small
		return (a);
	}
	sub = create_matrix(a.size - 1);
	x = 0;
	i = 0;
	x = 0;
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

double	determinant_2x2(t_matrix a)
{
	if (a.size == 2)
		return (a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0]);
	return (0);// Handle error: not a 2x2 matrix
}

/* Calculate the minor of a 3x3 matrix (the determinant of the submatrix). */

double	minor_3x3(t_matrix a, int row, int column)
{
	t_matrix	sub;
	double	det;

	if (a.size != 3)
	{
		// Handle error: not a 3x3 matrix
		return (0);
	}
	sub = submatrix(a, row, column);
	det = determinant_2x2(sub);
	free_matrix(sub);
	return (det);
}


/* Calculate the cofactor of a 3x3 matrix. */

double	cofactor_3x3(t_matrix a, int row, int column)
{
	double	minor;
	double	cofactor;

	minor = minor_3x3(a, row, column);
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
		det += a.matrix[0][i] * cofactor_3x3(a, 0, i);
		i++;
	}
	return (det);
}
