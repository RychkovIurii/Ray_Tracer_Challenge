/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/15 16:15:35 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

/* Calculate the determinant of a 2x2 matrix. */

double	determinant_2x2(t_matrix a)
{
	if (a.size != 2)
	{
		// Handle error: not a 2x2 matrix
		return (0);
	}
	return (a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0]);
}

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

