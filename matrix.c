/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/10 10:56:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Function to create a matrix of a given size.
Allocate memory for the matrix and initialize it with zeros.
** @param size: The size of the matrix.
** @return The matrix of the given size. */
/* t_matrix	create_matrix(int size)
{
	t_matrix	*matrix;
	int			i;
	int			j;

	matrix = (t_matrix *)calloc(1, sizeof(t_matrix));
	matrix->size = size;
	matrix->matrix = (double **)calloc(size, sizeof(double *));
	if (!matrix->matrix)
	{
		// Handle error: memory allocation failed
		printf("Memory allocation failed\n");
		return (*matrix);
	}
	i = 0;
	while (i < size)
	{
		matrix->matrix[i] = (double *)calloc(size, sizeof(double));
		if (matrix->matrix[i] == NULL)
		{
			// Handle error: memory allocation failed
			printf("Memory allocation failed\n");
			return (*matrix);
		}
		j = 0;
		while (j < size)
		{
			matrix->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (*matrix);
} */

t_matrix create_matrix(int size)
{
	t_matrix matrix;
	int i, j;

	matrix.size = size;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			matrix.matrix[i][j] = 0.0;
		}
	}
	return matrix;
}

/* Check if two matrices are equal. */
int	is_matrices_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	if (a.size != b.size)
		return (0);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			/* if (a.matrix[i][j] != b.matrix[i][j]) */
			if (fabs(a.matrix[i][j] - b.matrix[i][j]) > 1e-5) // 1e-5 is comparison within a small tolerance
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* Multiply two matrices. */
t_matrix	multiply_matrices(t_matrix a, t_matrix b)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	result = create_matrix(a.size);
	i = 0;
	while (i < a.size)
	{
		j = 0;
		while (j < a.size)
		{
			k = 0;
			while (k < a.size)
			{
				result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

/* Multiply a matrix by a tuple. */

// Don't sure what type of return value should be here!!!!
t_tuple	multiply_matrix_by_tuple(t_matrix a, t_tuple b)
{
	t_tuple	result;

	result.x = a.matrix[0][0] * b.x + a.matrix[0][1] * b.y + a.matrix[0][2] * b.z + a.matrix[0][3] * b.w;
	result.y = a.matrix[1][0] * b.x + a.matrix[1][1] * b.y + a.matrix[1][2] * b.z + a.matrix[1][3] * b.w;
	result.z = a.matrix[2][0] * b.x + a.matrix[2][1] * b.y + a.matrix[2][2] * b.z + a.matrix[2][3] * b.w;
	result.w = a.matrix[3][0] * b.x + a.matrix[3][1] * b.y + a.matrix[3][2] * b.z + a.matrix[3][3] * b.w;

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
t_matrix	multiply_matrix_by_identity_matrix(t_matrix a)
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
			result.matrix[i][j] = a.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

/* Multiply a tuple by the identity matrix. */

// Don't sure what type of return value should be here!!!!
t_tuple	multiply_identity_matrix_by_tuple(t_tuple a)
{
	t_tuple	result;

	result.x = a.x;
	result.y = a.y;
	result.z = a.z;
	result.w = a.w;
	return (result);
}

/* Transpose a matrix. */
t_matrix	transpose_matrix(t_matrix a)
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
			result.matrix[j][i] = a.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

/* Free the memory allocated for a matrix. */
void	free_matrix(t_matrix matrix)
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
}
