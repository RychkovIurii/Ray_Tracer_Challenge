/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:13:52 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 15:55:52 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix identity_matrix(int size)
{
	t_matrix id = create_matrix(size);
	for (int i = 0; i < size; i++)
		id.matrix[i][i] = 1;
	return id;
}

t_world default_world()
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
}


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
			//printf("array[j].t: %f\n", array[j].t);
			//printf("array[j + 1].t: %f\n", array[j + 1].t);
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
t_intersects intersect_world(t_world world, t_ray ray)
{
	t_intersects xs;
	t_intersects temp;
	t_intersection *temp_array;
	t_intersection *xs_array;
	int count = 0;
	int total_intersections = 0;
	temp_array = NULL;

	// Allocate memory for intersections dynamically (in case there are more than 2 intersections)
	xs_array = NULL;

	// Intersect all spheres in the world
	int i = 0;
	while(world.sphere[i] != NULL)
	{
		//printf("Intersecting sphere %d\n", i);
		temp = intersect_sphere(*world.sphere[i], ray);
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
		i++;
	}
	//printf("Before sorting:\n");
	/* for (int i = 0; i < total_intersections; i++) {
		printf("Intersection %d: t = %f\n", i, xs_array[i].t);
	} */

	// If there are any intersections, sort them
	if (total_intersections > 0) {
		bubble_sort_intersections(xs_array, total_intersections);
	}

	xs.count = total_intersections;
	xs.array = xs_array;
	return (xs);
}

/* The function ought to return the color at the intersection encapsulated by comps, in the given world.
** P.S. If we have more than one light source, we will have to loop through all of them and sum the results.
** @param world: t_world The world.
** @param comps: t_intersection The intersection.
** @return: t_tuple The color at the intersection.
*/
t_tuple	shade_hit(t_world world, t_intersection comps)
{
	int	shadowed;

	shadowed = is_shadowed(world, comps.point);
	return (lighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv, shadowed));
}

t_tuple	color_at(t_world world, t_ray ray)
{
	t_intersects	xs;
	t_intersection	*hits;
	t_intersection	comps;
	t_tuple			color;

	xs = intersect_world(world, ray);
	hits = hit(xs);
	if (hits == NULL)
	{
		//free(xs.array);
		return (create_color(0, 0, 0));
	}
	comps = prepare_computations(*hits, ray);
	color = shade_hit(world, comps);
	free(xs.array);
	return (color);
}


int is_shadowed(t_world world, t_tuple point)
{
	t_tuple	v;
	double	distance;
	t_ray	r;
	t_intersects	xs;
	t_intersection	*hits;
	int	i;

	v = substract_tuple(world.light.position, point);
	distance = magnitude(v);
	r = create_ray(point, normalize(v));
	xs = intersect_world(world, r);
	hits = hit(xs);
	i = 0;
	while (i < xs.count)
	{
		if (hits && hits[i].t < distance)
		{
			free(xs.array);
			return (1);
		}
		i++;
	}
	free(xs.array);
	return (0);
}
