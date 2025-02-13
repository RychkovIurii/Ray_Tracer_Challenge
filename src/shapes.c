/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:40:55 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/13 13:13:02 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_material default_material()
{
	t_material mat;
	mat.color = create_color(1, 1, 1);
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200.0;
	mat.has_pattern = 0;
	mat.reflective = 0.0;
	return (mat);
}

void free_intersects(t_intersects *xs)
{
	if (xs->array)
		free(xs->array);
	xs->array = NULL;
	xs->count = 0;
}

t_shape create_shape(t_shape_type type)
{
	t_shape	shape;

	shape.transform = identity_matrix(4);
	shape.material = default_material();
	shape.type = type;
	shape.center = point(0, 0, 0);
	shape.radius = 1;
	return (shape);
}

t_sphere create_sphere()
{
	t_sphere	sphere;

	sphere.base = create_shape(SHAPE_SPHERE);
	sphere.center = point(0, 0, 0);
	sphere.radius = 1;
	return (sphere);
}

void set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
}

t_intersects local_intersect_sphere(t_shape *sphere, t_ray transformed_ray)
{
	t_intersects result;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	sphere_to_ray = substract_tuple(transformed_ray.origin, sphere->center);
	a = dot(transformed_ray.direction, transformed_ray.direction);
	b = 2 * dot(transformed_ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		result.count = 0;
		result.array = NULL;
		return result;
	}

/* 	if (discriminant < EPSILON)
	{
		result.count = 1;
		result.array = (t_intersection *)calloc(1, sizeof(t_intersection));
		result.array[0].t = -b / (2 * a);
		result.array[0].object = sphere;
		return result;
	} */

	result.count = 2;
	result.array = (t_intersection *)calloc(2, sizeof(t_intersection));
	result.array[0].t = (-b - sqrt(discriminant)) / (2 * a);
	result.array[0].object = sphere;
	result.array[1].t = (-b + sqrt(discriminant)) / (2 * a);
	result.array[1].object = sphere;

	return result;
}

t_intersects local_intersect_plane(t_shape *plane, t_ray transformed_ray)
{
	t_intersects result;

	if (fabs(transformed_ray.direction.y) < EPSILON)
	{
		result.count = 0;
		result.array = NULL;
		return result;
	}
	result.count = 1;
	result.array = (t_intersection *)calloc(1, sizeof(t_intersection));
	result.array[0].t = -transformed_ray.origin.y / transformed_ray.direction.y;
	result.array[0].object = plane;
	return (result);
}

t_intersects intersect(t_shape *shape, t_ray ray)
{
	t_ray local_ray;

	local_ray = transform_ray(ray, inverse_matrix(shape->transform));
	shape->saved_ray = local_ray;
	if (shape->type == SHAPE_SPHERE)
	{
		return local_intersect_sphere(shape, local_ray);
	}
	else if (shape->type == SHAPE_PLANE)
	{
		return local_intersect_plane(shape, local_ray);
	}

	return (t_intersects){0, NULL};  // No intersections for unknown shapes
}

t_tuple local_normal_at_sphere(t_tuple sphere_center, t_tuple local_point)
{
	return (substract_tuple(local_point, sphere_center));
}

t_tuple local_normal_at_plane(t_tuple local_point)
{
	(void)local_point;
	return (vector(0, 1, 0));
}

t_tuple	normal_at(t_shape *shape, t_tuple world_point)
{
	t_tuple surface_normal;
	t_tuple world_normal;
	t_tuple local_point;
	t_tuple local_normal;
	t_matrix inverse_transform;

	inverse_transform = inverse_matrix(shape->transform);
	local_point = multiply_matrix_by_tuple(inverse_transform, world_point);
	if (shape->type == SHAPE_SPHERE)
	{
		local_normal = local_normal_at_sphere(shape->center, local_point);
	}
	else if (shape->type == SHAPE_PLANE)
	{
		local_normal = local_normal_at_plane(local_point);
	}
	world_normal = multiply_matrix_by_tuple(transpose_matrix(inverse_transform), local_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}
