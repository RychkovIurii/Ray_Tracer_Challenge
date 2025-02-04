/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_round_to_canvas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:40:59 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 13:38:00 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* a program that casts rays at a sphere
and draws the picture to a canvas. Any ray that hits the sphere should result in
a colored pixel (red, for example), and any miss should be drawn in black.
The result will be a silhouette of the sphere—not three-dimensional, but
definitely round! */

t_tuple	normal_at(t_sphere sphere, t_tuple world_point);

int main()
{
	t_canvas	*canvas;
	t_tuple		red, black;
	t_tuple		position;	// Point on the wall
	t_ray		ray;		// Ray from the eye to the wall
	int			i;
	int			j;
	double		world_x;
	double		world_y;

	int canvas_pixels = 100;
	double wall_z = 10.0;
	double wall_size = 7.0;
	double half = wall_size / 2;
	double pixel_size = wall_size / canvas_pixels;

	// Ray origin
	t_tuple ray_origin = point(0, 0, -5);

	// Create the sphere
	t_sphere sphere = {point(0, 0, 0), 1, identity_matrix(4)};

	// Create the canvas
	canvas = create_canvas(canvas_pixels, canvas_pixels);

	// Create the color
	red = create_color(1, 0, 0); // red
	black = create_color(0, 0, 0); // black

	// Set the sphere's transform
	//set_transform(&sphere, scaling_matrix(1, 0.5, 1)); // round1.ppm
	//set_transform(&sphere, scaling_matrix(0.5, 1, 1)); // round2.ppm
	//set_transform(&sphere, multiply_matrices (rotation_z_matrix(M_PI / 4), scaling_matrix(0.5, 1, 1))); // round3.ppm
	set_transform(&sphere, multiply_matrices(shearing_matrix(1, 0, 0, 0, 0, 0), scaling_matrix(0.5, 1, 1))); // round4.ppm


	// Cast rays
	for (int y = 0; y < canvas_pixels; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			world_x = -half + pixel_size * x;
			position = point(world_x, world_y, wall_z);
			ray = create_ray(ray_origin, normalize(substract_tuple(position, ray_origin)));

			// Check for intersection
			t_intersects xs = intersect_sphere(sphere, ray);
			t_intersection *hit_intersection = hit(xs);

			if (hit_intersection != NULL)
			{
				// If hit, color the pixel red
				write_pixel(canvas, x, y, red);
			}
			else
			{
				// If miss, color the pixel black
				write_pixel(canvas, x, y, black);
			}

			if (xs.array != NULL)
				free(xs.array);
		}
	}
	canvas_to_ppm(canvas, "round4.ppm");
	return (0);
}