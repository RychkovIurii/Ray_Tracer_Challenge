/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:09:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 17:27:32 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Submatrix returns a copy of the given matrix with the given row and column removed. */
t_matrix3x3	*submatrix3x3(t_matrix3x3 *a, int row, int column)
{
	t_matrix3x3	sub;
	int			i;
	int			j;
	int			x;
	int			y;

	ft_bzero(&sub, sizeof(t_matrix3x3));
	x = 0;
	i = 0;
	x = 0;
	while (i < 3)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		y = 0;
		while (j < 3)
		{
			if (j == column)
			{
				j++;
				continue;
			}
			sub[i][j] = *a[i][j];
			y++;
			j++;
		}
		x++;
		i++;
	}
	return (sub);
}

t_matrix4x4 *submatrix4x4(t_matrix4x4 *a, int row, int column)
{
	t_matrix4x4	sub;
	int			i;
	int			j;
	int			x;
	int			y;

	ft_bzero(&sub, sizeof(t_matrix4x4));
	x = 0;
	i = 0;
	x = 0;
	while (i < 4)
	{
		if (i == row)
		{
			i++;
			continue;
		}
		j = 0;
		y = 0;
		while (j < 4)
		{
			if (j == column)
			{
				j++;
				continue;
			}
			sub[i][j] = *a[i][j];
			y++;
			j++;
		}
		x++;
		i++;
	}
	return (sub);
}


/* Calculate the minor of matrix 3x3. */
double	minor_matrix3x3(t_matrix3x3 a, int row, int column)
{
	double	minor;
	t_matrix2x2	*sub;

	ft_bzero(&sub, sizeof(t_matrix2x2));
	sub = submatrix2x2(a, row, column);
	minor = determinant2x2(sub);
	return (minor);
}

double minor_matrix4x4(t_matrix4x4 a, int row, int column)
{
	double	minor;
	t_matrix3x3	*sub;


	ft_bzero(&sub, sizeof(t_matrix3x3));
	sub = submatrix3x3(a, row, column);
	minor = determinant3x3(sub);
	return (minor);
}


/* Calculate the cofactor of a 3x3 matrix. */
double	cofactor_matrix3x3(t_matrix3x3 a, int row, int column)
{
	double	minor;
	double	cofactor;

	minor = minor_matrix3x3(a, row, column);
	if ((row + column) % 2 == 0)
		cofactor = minor;
	else
		cofactor = -minor;
	return (cofactor);
}

/* Calculate the cofactor of a 4x4 matrix. */
double	cofactor_matrix4x4(t_matrix4x4 a, int row, int column)
{
	double	minor;
	double	cofactor;

	minor = minor_matrix4x4(a, row, column);
	if ((row + column) % 2 == 0)
		cofactor = minor;
	else
		cofactor = -minor;
	return (cofactor);
}

/* Calculate the determinant of a matrix2x2. */
double	determinant2x2(t_matrix2x2 *a)
{
	double	det;

	det = (*a[0][0]) * (*a[1][1]) - (*a[0][1]) * (*a[1][0]);
	return (det);
}

/* Calculate the determinant of a matrix3x3. */
double	determinant3x3(t_matrix3x3 *a)
{
	double	det;
	int		i;

	det = 0;
	i = 0;
	while (i < 3)
	{
		det += (*a[0][i]) * cofactor_matrix3x3(a, 0, i);
		i++;
	}
	return (det);
}	

/* Calculate the determinant of a matrix4x4. */
double	determinant4x4(t_matrix4x4 *a)
{
	double	det;
	int		i;
	int		j;

	det = 0;
	i = 0;
	while (i < 4)
	{
		det += (*a[0][i]) * cofactor_matrix4x4(a, 0, i);
		i++;
	}
	return (det);
}

/* Is matrix invertible */
/* int		is_invertible(t_matrix4x4 a)
{
	if (determinant(a) == 0)
		return (0);
	return (1);
} */

/* Inverse matrix. */
void	inverse_matrix(t_matrix4x4 *out, t_matrix4x4 *in)
{
	double		det;
	int			i;
	int			j;

	det = determinant4x4(*in);
	if (det == 0)
	{
		ft_bzero(out, sizeof(t_matrix4x4));
		return ;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			(*out)[j][i] = cofactor_matrix4x4(*in, i, j) / det;
			j++;
		}
		i++;
	}
}
