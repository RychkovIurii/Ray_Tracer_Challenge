/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/29 12:11:28 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "matrix.h"

/* typedef enum e_object_type
{
	t_sphere,
	t_plane,
	t_cylinder,
	t_cone,
	t_triangle
}				t_object_type; */

/* typedef struct	s_object
{
	int			type;
	void		*data; // should think about this
}				t_object; */

typedef struct	s_ray
{
	t_tuple		origin;		//point
	t_tuple		direction;	//vector
}				t_ray;

typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
	t_matrix	transform;
}				t_sphere;

typedef struct	s_intersection // t value and object
{
	double		t;
	t_sphere	*object;
}				t_intersection;

typedef struct	s_intersects // array of intersections
{
	int					count;
	t_intersection		*array;
}						t_intersects;


