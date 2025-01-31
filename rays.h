/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 11:28:14 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "mini_rt.h"

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



/* typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
	t_matrix	transform;
}				t_sphere; */


/* Function to work with rays. */
t_ray			create_ray(t_tuple origin, t_tuple direction);
t_tuple			get_ray_position(t_ray ray, double t);
t_ray	transform_ray(t_ray ray, t_matrix matrix);
t_intersects	intersect_sphere(t_sphere sphere, t_ray ray);
t_intersection	*hit(t_intersects intersections);
void set_transform(t_sphere *sphere, t_matrix transform);

#endif
