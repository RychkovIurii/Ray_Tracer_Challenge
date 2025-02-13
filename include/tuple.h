/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:54:15 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/12 16:07:09 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include "mini_rt.h"


/* Functions to work with tuples. */

t_tuple		create_tuple(double x, double y, double z, double w);
t_tuple		point(double x, double y, double z);
t_tuple		vector(double x, double y, double z);
t_tuple		add_tuple(t_tuple a, t_tuple b);
t_tuple		substract_tuple(t_tuple a, t_tuple b);
t_tuple		negate_tuple(t_tuple a);
t_tuple		multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple		divide_tuple(t_tuple a, double scalar);
int			is_tuples_equal(t_tuple a, t_tuple b);
int			is_point(t_tuple a);
int			is_vector(t_tuple a);


/* Functions to work with vectors. */

double	magnitude(t_tuple v);
t_tuple	normalize(t_tuple v);
double	dot(t_tuple a, t_tuple b);
t_tuple	cross(t_tuple a, t_tuple b);
t_tuple reflect(t_tuple in, t_tuple normal);


/* Functions to work with colors. */

t_tuple	create_color(double r, double g, double b);
t_tuple	multiply_color(t_tuple a, t_tuple b);

#endif
