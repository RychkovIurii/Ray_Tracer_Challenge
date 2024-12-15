/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:54:15 by irychkov          #+#    #+#             */
/*   Updated: 2024/12/15 18:26:44 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define EPSILON	0.0001f

/* We set to 1.0 to make it a point, and 0.0 to make it a vector. */

typedef struct	s_tuple
{
	double x;
	double y;
	double z;
	double w;
}	t_tuple;
