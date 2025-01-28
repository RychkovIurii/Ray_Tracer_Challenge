/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/28 14:47:36 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

typedef enum e_object_type
{
	t_sphere,
	t_plane,
	t_cylinder,
	t_cone,
	t_triangle
}				t_object_type;

typedef struct	s_object
{
	int			type;
	void		*data; // should think about this
}				t_object;

typedef struct	s_ray
{
	t_tuple		origin;		//point
	t_tuple		direction;	//vector
}				t_ray;

typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
}				t_sphere;

typedef struct	s_intersect // array of intersections

{
	int					count;
	t_intersection		*array;
}						t_intersect;

typedef struct	s_intersection // t value and object
{
	double		t;
	t_object	*object;
}				t_intersection;

t_ray			create_ray(t_tuple origin, t_tuple direction)
{
	t_ray		result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_tuple			get_ray_position(t_ray ray, double t)
{
	t_tuple		result;

	result = add_tuple(ray.origin, multiply_tuple_scalar(ray.direction, t));
	return (result);
}


/* t_intersection create_intersection(double t, t_object *object)
{
	t_intersection result;

	result.t = t;
	result.object = object;
	return (result);
} */

/*
	Function reurns the number of intersections between the ray and the sphere
	and the values of t at which the intersections occur.
	Lowest value of t is a hit closest to the ray's origin.
	Hit is a point where the ray intersects the sphere.
	We need all values for reflections and refractions.
*/
t_intersect	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_intersect result;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_intersection	intersection1;
	t_intersection	intersection2;

	sphere_to_ray = substract_tuple(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		result.count = 0;
		result.array = NULL;
		return (result);
	}
	intersection1.t = (-b - sqrt(discriminant)) / (2 * a);
	intersection1.object = &sphere;
	intersection2.t = (-b + sqrt(discriminant)) / (2 * a);
	intersection2.object = &sphere;
	result.count = 2;
	result.array = (t_intersection *)malloc(sizeof(t_intersection) * 2);
	result.array[0] = intersection1;
	result.array[1] = intersection2;
	return (result);
}
