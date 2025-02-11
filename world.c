/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:13:52 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/11 14:31:15 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_tuple			color_at(t_world *world, t_ray ray, int remaining);

t_matrix identity_matrix(int size)
{
	t_matrix id = create_matrix(size);
	for (int i = 0; i < size; i++)
		id.matrix[i][i] = 1;
	return id;
}

/* t_world default_world()
{
	t_world world;
	t_sphere *sphere1;
	t_sphere *sphere2;

	// Allocate memory for spheres
	sphere1 = (t_sphere *)calloc(1, sizeof(t_sphere));
	sphere2 = (t_sphere *)calloc(1, sizeof(t_sphere));

	// Initialize the properties of sphere1
	sphere1->material = material(create_color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
	sphere1->transform = identity_matrix(4);
	sphere1->center = point(0, 0, 0);
	sphere1->radius = 1;

	// Initialize the properties of sphere2
	sphere2->material = material(create_color(1, 0, 0), 0.1, 0.7, 0.2, 200.0);
	sphere2->transform = scaling_matrix(0.5, 0.5, 0.5);
	sphere2->center = point(0, 0, 0);
	sphere2->radius = 0.5;

	// Initialize the light
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

	// Allocate memory for the sphere array in the world
	world.sphere = (t_sphere **)calloc(3, sizeof(t_sphere *));
	world.sphere[0] = sphere1;
	world.sphere[1] = sphere2;

	return (world);
} */


void	bubble_sort_intersections(t_intersection *array, int count)
{
	t_intersection temp;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - 1)
		{
			if (array[j].t > array[j + 1].t)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Function to find the intersections in the world
t_intersects intersect_world(t_world *world, t_ray ray)
{
	t_intersects xs;
	t_intersection *temp_array;
	t_intersection *xs_array;
	t_intersects temp;
	int count = 0;
	int total_intersections = 0;
	temp_array = NULL;

	// Allocate memory for intersections dynamically (in case there are more than 2 intersections)
	xs_array = NULL;

	// Intersect all spheres in the world
	int i = 0;
	while(world->shapes[i] != NULL)
	{
		temp = intersect(world->shapes[i], ray);
		temp_array = temp.array;
		
		// If there are any intersections, resize the array and copy them
		if (temp.count > 0) {
			// Resize the xs_array to hold all intersections
			xs_array = realloc(xs_array, sizeof(t_intersection) * (total_intersections + temp.count));
			// Copy new intersections to the xs_array
			for (int j = 0; j < temp.count; j++) {
				xs_array[total_intersections + j] = temp_array[j];
			}
			total_intersections += temp.count;
		}
		free_intersects(&temp);
		i++;
	}

	// If there are any intersections, sort them
	if (total_intersections > 0) {
		bubble_sort_intersections(xs_array, total_intersections);
	}
	xs.count = total_intersections;
	xs.array = xs_array;
	return (xs);
}


t_tuple reflected_color(t_world *world, t_intersection comps, int remaining, t_intersects *xs)
{
	t_tuple	color;
	t_ray	reflected_ray;
	t_tuple	reflect_color;

	if (remaining <= 0)
		return (create_color(0, 0, 0));
	if (comps.object->material.reflective == 0)
		return (create_color(0, 0, 0));
	reflected_ray = create_ray(comps.over_point, comps.reflectv);
/* 	if (remaining < DEFAULT_REMAINING)
	{
		free(xs->array);
		xs->array = NULL;
	} */
	color = color_at(world, reflected_ray, remaining - 1);
	reflect_color = multiply_tuple_scalar(color, comps.object->material.reflective);
	return (reflect_color);
}

t_tuple refracted_color(t_world *world, t_intersection comps, int remaining, t_intersects *xs)
{
	t_tuple	refract_color;
	t_ray	refracted_ray;
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	double	cos_t;
	t_tuple	direction;
	t_intersection	*hit_obj;

	if (remaining <= 0)
		return (create_color(0, 0, 0));
	if (comps.object->material.transparency == 0)
		return (create_color(0, 0, 0));
	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.eyev, comps.normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1)
		return (create_color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	direction = substract_tuple(multiply_tuple_scalar(comps.normalv, n_ratio * cos_i - cos_t), multiply_tuple_scalar(comps.eyev, n_ratio));
	refracted_ray = create_ray(comps.under_point, direction);
/* 	if (remaining < DEFAULT_REMAINING)
	{
		free(xs->array);
		xs->array = NULL;
	} */
	refract_color = color_at(world, refracted_ray, remaining - 1);
	return (multiply_tuple_scalar(refract_color, comps.object->material.transparency));
}

double schlick(t_intersection comps)
{
	double	cos;
	double	n_ratio;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos = dot(comps.eyev, comps.normalv);
	if (comps.n1 > comps.n2)
	{
		n_ratio = comps.n1 / comps.n2;
		sin2_t = n_ratio * n_ratio * (1 - cos * cos);
		if (sin2_t > 1)
			return (1.0);
		cos_t = sqrt(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
	return (r0 + (1 - r0) * pow(1 - cos, 5));
}


/* The function ought to return the color at the intersection encapsulated by comps, in the given world.
** P.S. If we have more than one light source, we will have to loop through all of them and sum the results.
** @param world: t_world The world.
** @param comps: t_intersection The intersection.
** @return: t_tuple The color at the intersection.
*/
t_tuple	shade_hit(t_world *world, t_intersection comps, int remaining, t_intersects *xs)
{
	int	shadowed;
	t_tuple	surface;
	t_tuple reflected;
	t_tuple refracted;
	double	reflectance;
	t_tuple	color;

	shadowed = is_shadowed(*world, comps.over_point);
	surface = lighting(comps.object->material, *comps.object, world->light, comps.over_point, comps.eyev, comps.normalv, shadowed);
	reflected = reflected_color(world, comps, remaining, xs);
	refracted = refracted_color(world, comps, remaining, xs);
	// If the material is both reflective and transparent, use Schlick's approximation.
	if (comps.object->material.transparency > 0 && comps.object->material.reflective > 0)
	{
		reflectance = schlick(comps);  // Compute the reflectance at the intersection.
		color = add_tuple(surface,
				add_tuple(multiply_tuple_scalar(reflected, reflectance),
						multiply_tuple_scalar(refracted, 1.0 - reflectance)));
	}
	else if (comps.object->material.transparency > 0)
	{
		color = add_tuple(surface, refracted);
	}
	else
	{
		color = add_tuple(surface, reflected);
	}
	return (color);
}

t_tuple	color_at(t_world *world, t_ray ray, int remaining)
{
	t_intersects	xs;
	t_intersection	*hits;
	t_intersection	comps;
	t_tuple			color;

	xs = intersect_world(world, ray);
	hits = hit(xs);
	if (hits == NULL)
	{
		free(xs.array);
		xs.array = NULL;
		return (create_color(0, 0, 0));
	}
	comps = prepare_computations(*hits, ray, &xs);
	color = shade_hit(world, comps, remaining, &xs);
	free(xs.array);
	xs.array = NULL;
	return (color);
}


int is_shadowed(t_world world, t_tuple point)
{
	t_tuple	v;
	double	distance;
	t_ray	r;
	t_intersects	xs;
	t_intersection	*hit_obj;
	int	i;

	v = substract_tuple(world.light.position, point);
	distance = magnitude(v);
	r = create_ray(point, normalize(v));
	xs = intersect_world(&world, r);
	hit_obj = hit(xs);
	if (hit_obj && hit_obj->t < distance)
	{
		free_intersects(&xs);
		return (1);
	}
	free_intersects(&xs);
	return (0);
}
