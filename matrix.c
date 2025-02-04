/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 17:15:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Function to create a matrix of a given size.
Allocate memory for the matrix and initialize it with zeros.
** @param size: The size of the matrix.
** @return The matrix of the given size. */
/* t_matrix	create_matrix(int size)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix.size = size;
	matrix.matrix = (double **)calloc(size, sizeof(double *));
	if (!matrix.matrix)
	{
		// Handle error: memory allocation failed
		printf("Memory allocation failed\n");
		return (matrix);
	}
	i = 0;
	while (i < size)
	{
		matrix.matrix[i] = (double *)calloc(size, sizeof(double));
		if (!matrix.matrix[i])
		{
			// Handle error: memory allocation failed
			printf("Memory allocation failed\n");
			return (matrix);
		}
		j = 0;
		while (j < size)
		{
			matrix.matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
} */

/* Check if two matrices are equal. */
int	is_matrices4x4_equal(t_matrix4x4 a, t_matrix4x4 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			/* if (a.matrix[i][j] != b.matrix[i][j]) */
			if (fabs(a[i][j] - b[i][j]) > 1e-5) // 1e-5 is comparison within a small tolerance
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* Check if two matrices are equal. */
int is_matrices3x3_equal(t_matrix3x3 a, t_matrix3x3 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (fabs(a[i][j] - b[i][j]) > 1e-5)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* Check if two matrices are equal. */
int is_matrices2x2_equal(t_matrix2x2 a, t_matrix2x2 b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (fabs(a[i][j] - b[i][j]) > 1e-5)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* Multiply two matrices. */
void	multiply_matrices(t_matrix4x4	*result, t_matrix4x4 *a, t_matrix4x4 *b)
{
	int			i;
	int			j;
	int			k;

	i = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				*result[i][j] += (*a[i][k]) * (*b[k][j]);
				k++;
			}
			j++;
		}
		i++;
	}
}

/* Multiply a matrix by a tuple. */

// Don't sure what type of return value should be here!!!!
t_tuple	multiply_matrix_by_tuple(t_matrix4x4 a, t_tuple b)
{
	t_tuple	result;

	result.x = a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z + a[0][3] * b.w;
	result.y = a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z + a[1][3] * b.w;
	result.z = a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z + a[2][3] * b.w;
	result.w = a[3][0] * b.x + a[3][1] * b.y + a[3][2] * b.z + a[3][3] * b.w;

	return (result);
}

/* t_matrix 	multiply_matrix_by_tuple(t_matrix a, t_tuple b)
{
	t_matrix	result;
	int			i;
	int			j;

	result = create_matrix(a.size); //shall we create a new matrix here?
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			result.matrix[i][j] = a.matrix[i][0] * b.x + a.matrix[i][1] * b.y + a.matrix[i][2] * b.z + a.matrix[i][3] * b.w;
			j++;
		}
		i++;
	}
	return (result);
} */

/* Multiply a matrix by the identity matrix. */
/* t_matrix	multiply_matrix_by_identity_matrix(t_matrix a)
{
	t_matrix	result;
	int			i;
	int			j;

	set_identity_matrix(&result, a.size); //shall we create a new matrix here?
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			result.matrix[i][j] = a.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
} */

/* Multiply a tuple by the identity matrix. */

// Don't sure what type of return value should be here!!!!
/* t_tuple	multiply_identity_matrix_by_tuple(t_tuple a)
{
	t_tuple	result;

	result.x = a.x;
	result.y = a.y;
	result.z = a.z;
	result.w = a.w;
	return (result);
} */

/* Transpose a matrix. */
void	transpose_matrix(t_matrix4x4 *out, t_matrix4x4 *in)
{
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			*out[j][i] = *in[i][j];
			j++;
		}
		i++;
	}
}

/* Free the memory allocated for a matrix. */
/* void	free_matrix(t_matrix matrix)
{
	int	i;

	i = 0;
	if (!matrix.matrix)
		return;
	while (i < matrix.size)
	{
		free(matrix.matrix[i]);
		i++;
	}
	free(matrix.matrix);
} */
