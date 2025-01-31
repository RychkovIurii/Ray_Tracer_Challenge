/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:54 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 15:44:41 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "mini_rt.h"

/* Functions to work with matrices. */

t_matrix	create_matrix(int size);
int			is_matrices_equal(t_matrix a, t_matrix b);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_by_tuple(t_matrix a, t_tuple b);
t_matrix	multiply_matrix_by_identity_matrix(t_matrix a);
t_tuple		multiply_identity_matrix_by_tuple(t_tuple a);
t_matrix	transpose_matrix(t_matrix a);
void		free_matrix(t_matrix matrix);
t_matrix	submatrix(t_matrix a, int row, int column);
double		minor_matrix(t_matrix a, int row, int column);
double		cofactor_matrix(t_matrix a, int row, int column);
double		determinant(t_matrix a);
t_matrix	inverse_matrix(t_matrix a);
t_matrix	translation_matrix(double x, double y, double z);
t_matrix	scaling_matrix(double x, double y, double z);
t_matrix	rotation_x_matrix(double radian);
t_matrix	rotation_y_matrix(double radian);
t_matrix	rotation_z_matrix(double radian);
t_matrix	shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);

#endif
