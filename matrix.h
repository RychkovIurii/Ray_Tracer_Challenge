/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:10:54 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/15 15:40:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "tuple.h"

typedef struct	s_matrix
{
	int			size;
	double		**matrix;
}				t_matrix;

t_matrix	create_matrix(int size);
int			is_matrices_equal(t_matrix a, t_matrix b);
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_by_tuple(t_matrix a, t_tuple b);
t_matrix	multiply_matrix_by_identity_matrix(t_matrix a);
t_tuple		multiply_identity_matrix_by_tuple(t_tuple a);
t_matrix	transpose_matrix(t_matrix a);
void		free_matrix(t_matrix matrix);

#endif
