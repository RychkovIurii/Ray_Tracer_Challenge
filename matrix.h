/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:54 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 17:00:24 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "mini_rt.h"

/* Functions to work with matrices. */

/* t_matrix	create_matrix(int size); */
int			is_matrices2x2_equal(t_matrix2x2 a, t_matrix2x2 b);
int			is_matrices3x3_equal(t_matrix3x3 a, t_matrix3x3 b);
int			is_matrices4x4_equal(t_matrix4x4 a, t_matrix4x4 b);
void		multiply_matrices(t_matrix4x4 result, t_matrix4x4 *a, t_matrix4x4 *b);
t_tuple		multiply_matrix_by_tuple(t_matrix4x4 a, t_tuple b);
void		transpose_matrix(t_matrix4x4 *out, t_matrix4x4 *in);
/* void		free_matrix(t_matrix matrix); */
t_matrix3x3	*submatrix3x3(t_matrix3x3 *a, int row, int column);
t_matrix4x4	*submatrix4x4(t_matrix4x4 *a, int row, int column);
double		minor_matrix3x3(t_matrix3x3 a, int row, int column);
double		minor_matrix4x4(t_matrix4x4 a, int row, int column);
double		cofactor_matrix3x3(t_matrix3x3 a, int row, int column);
double		cofactor_matrix4x4(t_matrix4x4 a, int row, int column);
double		determinant2x2(t_matrix2x2 *a);
double		determinant3x3(t_matrix3x3 *a);
double		determinant4x4(t_matrix4x4 *a);
void		inverse_matrix(t_matrix4x4 *out, t_matrix4x4 *in);
t_matrix4x4	*translation_matrix(double x, double y, double z);
t_matrix4x4	*scaling_matrix(double x, double y, double z);
t_matrix4x4	*rotation_x_matrix(double radian);
t_matrix4x4	*rotation_y_matrix(double radian);
t_matrix4x4	*rotation_z_matrix(double radian);
t_matrix4x4	*shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);

#endif
