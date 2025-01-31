/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:13:52 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 18:13:30 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct world
{
	t_light		light;
	t_sphere	**sphere;
}				t_world;

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
	sphere1 = (t_sphere *)malloc(sizeof(t_sphere));
	sphere2 = (t_sphere *)malloc(sizeof(t_sphere));

	// Initialize the properties of sphere1
	sphere1->material = material(create_color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
	sphere1->transform = identity_matrix(4);
	sphere1->center = point(0, 0, 0);
	sphere1->radius = 1;

	// Initialize the properties of sphere2
	sphere2->material = material(create_color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
	sphere2->transform = scaling_matrix(0.5, 0.5, 0.5);
	sphere2->center = point(0, 0, 0);
	sphere2->radius = 0.5;

	// Initialize the light
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

	// Allocate memory for the sphere array in the world
	world.sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 2);
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

	// Allocate memory for intersections dynamically (in case there are more than 2 intersections)
	xs_array = NULL;

	// Intersect all spheres in the world
	for (int i = 0; i < 2; i++) {
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

/* int main()
{
	t_world w = default_world();
	t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersects xs = intersect_world(w, r);
	t_intersection *hits = hit(xs);
	if (hits != NULL && hits->t == 4)
		printf("Test passed\n Hit point: %f\n", hits->t);
	else
		printf("Test failed\n Hit point: %f\n", hits->t);
	free(xs.array);
	free(w.sphere[0]);
	free(w.sphere[1]);
	free(w.sphere);
	return (0);
}
 */