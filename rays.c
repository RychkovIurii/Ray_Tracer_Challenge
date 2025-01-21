/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/21 12:03:07 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

typedef struct	s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
}				t_sphere;

typedef struct	s_sphere_intersection
{
	int 		count;
	double		t1;
	double		t2;
}				t_sphere_intersection;

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

double 			intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;

	sphere_to_ray = substract_tuple(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > t2)
	{
		double tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	return (t1);
}
