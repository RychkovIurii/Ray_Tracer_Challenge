/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:30:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/28 12:12:52 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

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

typedef struct	s_sphere_intersection
{
	double	t1;
	double	t2;
}				t_sphere_intersection;

typedef struct	s_intersection
{
	double		t;
	t_sphere	sphere;
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

/*
	Function reurns the number of intersections between the ray and the sphere
	and the values of t at which the intersections occur.
	Lowest value of t is a hit closest to the ray's origin.
	Hit is a point where the ray intersects the sphere.
	We need all values for reflections and refractions.
*/
t_sphere_intersection intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_sphere_intersection result;
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
	{
		memset(&result, 0, sizeof(t_sphere_intersection));
	}
	else
	{
		result.t1 = (-b - sqrt(discriminant)) / (2 * a);
		result.t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (result.t1 > result.t2)
		{
			double temp = result.t1;
			result.t1 = result.t2;
			result.t2 = temp;
		}
	}
	return (result);
}

double hit(t_sphere_intersection intersections)
{
	if (intersections.count == 0)
		return (-1);
	if (intersections.count == 1)
		return (intersections.t1);
	if (intersections.t1 < intersections.t2)
		return (intersections.t1);
	else
		return (intersections.t2);
}
