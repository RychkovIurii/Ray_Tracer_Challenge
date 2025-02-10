/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_reflection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:19 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/10 14:19:37 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int main()
{
	t_world world;

	// Allocate memory for the shapes in the world
	world.shapes = (t_shape **)calloc(6, sizeof(t_shape *));

	// Floor
	t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
	floor->center = point(0, 0, 0);
	floor->radius = 0;
	floor->type = SHAPE_PLANE;
	floor->transform = identity_matrix(4);
	floor->material = material(create_color(0.9, 0.9, 0.9), 0.1, 0.9, 0, 200.0, PATTERN_CHECKER);
	floor->material.pattern = stripe_pattern(create_color(1, 1, 1), create_color(0.902, 0.067, 0.6));
	floor->material.pattern.transform = scaling_matrix(0.3, 0.3, 0.3);
	floor->material.reflective = 0.7;
	world.shapes[0] = floor;

	// wall or ceiling
	t_shape *ceil = (t_shape *)calloc(1, sizeof(t_shape));
	ceil->center = point(0, 0, 0);
	ceil->radius = 0;
	ceil->type = SHAPE_PLANE;
	t_matrix rot_x1 = rotation_x_matrix(M_PI / 2);
	t_matrix transl1 = translation_matrix(0, 5, 5);
	ceil->transform = multiply_matrices(transl1, rot_x1);
	ceil->material = material(create_color(0.9, 0.9, 0.9), 0.1, 0.9, 0, 200.0, PATTERN_STRIPE);
	ceil->material.pattern = stripe_pattern(create_color(1, 1, 1), create_color(0.784, 0.82, 0.796));
	ceil->material.reflective = 0.2;
	world.shapes[1] = ceil;


	// Middle shapes
	t_shape *middle = (t_shape *)calloc(1, sizeof(t_shape));
	middle->center = point(0, 0, 0);
	middle->radius = 1;
	middle->type = SHAPE_SPHERE;
	middle->transform = translation_matrix(-0.5, 1, 0.5);
	middle->material = material(create_color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0, PATTERN_RING);
	middle->material.pattern = stripe_pattern(create_color(0.125, 0.91, 0.408), create_color(0.91, 0.518, 0.125));
	t_matrix rot_x0 = rotation_x_matrix(M_PI / 2);
	t_matrix transl0 = scaling_matrix(0.1, 0.1, 0.1);
	middle->material.pattern.transform = multiply_matrices(transl0, rot_x0);
	//middle->material.pattern.transform = multiply_matrices(scaling_matrix(0.1, 0.1, 0.1), rotation_y_matrix(M_PI / 4));
	middle->material.reflective = 0.5;
	world.shapes[2] = middle;

	// Right shapes
	t_shape *right = (t_shape *)calloc(1, sizeof(t_shape));
	right->center = point(0, 0, 0);
	right->radius = 1;
	right->type = SHAPE_SPHERE;
	right->transform = multiply_matrices(
		translation_matrix(1.5, 0.5, -0.5),
		scaling_matrix(0.5, 0.5, 0.5));
	right->material = material(create_color(0.816, 0.753, 0.98), 0.1, 0.7, 0.3, 200.0, PATTERN_GRADIENT);
	right->material.pattern = stripe_pattern(create_color(0.318, 0.106, 0.859), create_color(0.78, 0.729, 0.922));
	right->material.pattern.transform = rotation_y_matrix(M_PI / 2);
	right->material.reflective = 0.5;
	world.shapes[3] = right;

	// Left shapes
	t_shape *left = (t_shape *)calloc(1, sizeof(t_shape));
	left->center = point(0, 0, 0);
	left->radius = 1;
	left->type = SHAPE_SPHERE;
	left->transform = multiply_matrices(
		translation_matrix(-1.5, 0.33, -0.75),
		scaling_matrix(0.33, 0.33, 0.33));
	left->material = material(create_color(1, 1, 1), 0.1, 0.7, 0.3, 200.0, PATTERN_NONE);
	left->material.pattern = stripe_pattern(create_color(0.031, 0.49, 0.086), create_color(0.914, 0.98, 0.02));
	left->material.reflective = 0.5;
	world.shapes[4] = left;

	// Light source
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));


	// Camera
	t_camera camera = create_camera(800, 400, M_PI / 3);
	camera.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	// Render the scene
	t_canvas *canvas = render(camera, world);

	// Save the canvas to a file
	canvas_to_ppm(canvas, "reflective.ppm");

	// Free allocated memory
	free_canvas(canvas);
	free(floor);
	free(ceil);
	free(middle);
	free(right);
	free(left);
	free(world.shapes);

	return 0;
}