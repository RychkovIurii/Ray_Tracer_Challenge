/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:43:45 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/11 18:22:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

int main()
{
	t_world world;

	// Allocate memory for the shapes in the world
	world.shapes = (t_shape **)calloc(3, sizeof(t_shape *));

	// 1. Floor
    t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
    floor->center = point(0, 0, 0);
    floor->radius = 0;
    floor->type = SHAPE_PLANE;
    floor->transform = translation_matrix(0, -1, 0);
    floor->material = material(create_color(0.9, 0.9, 0.9), 0.1, 0.9, 0, 200.0, PATTERN_CHECKER);
    floor->material.pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));
    floor->material.pattern.transform = scaling_matrix(0.3, 0.3, 0.3);
    floor->material.reflective = 0.3;
    floor->material.transparency = 0.0;
    floor->material.refractive_index = 1.5;
    world.shapes[0] = floor;


	// 2. Glass sphere
    t_shape *bottom_sphere = (t_shape *)calloc(1, sizeof(t_shape));
    bottom_sphere->center = point(0, 0, 0);
    bottom_sphere->radius = 1;
    bottom_sphere->type = SHAPE_SPHERE;
    bottom_sphere->transform = translation_matrix(0, 0, -0.5);
    bottom_sphere->material = material(create_color(1, 1, 1), 0.05, 0.0, 0.0, 200.0, 0);
	bottom_sphere->material.reflective = 1.0;
    bottom_sphere->material.transparency = 1.0;
    bottom_sphere->material.refractive_index = 1.5;
    world.shapes[1] = bottom_sphere;

	// Light source
	world.light = point_light(point(7, 10, -5), create_color(1, 1, 1));


	// Camera:
    // For a top-down view, place the camera high above and look at the scene center.
    // Here, we position the camera at (0, 10, 0) looking toward (0, 0, 0). Since the view
    // direction is vertical, we choose an up vector that is not parallel to it; for example, (0, 0, -1).
	t_camera camera = create_camera(200, 100, M_PI / 3);
	camera.transform = view_transform(point(0, 5, -10), point(0, 0, 0), vector(0, 1, 0));

    // Camera: choose a viewpoint that clearly shows the ball on the floor.
    // For example, placing the camera at (0, 5, -10) looking toward (0, 0, 0) with up as (0,1,0)
/*     t_camera camera = create_camera(200, 100, M_PI / 3);
    camera.transform = view_transform(point(0, 5, -10), point(0, 0, 0), vector(0, 1, 0)); */

	// Render the scene
	t_canvas *canvas = render(camera, &world);

	// Save the canvas to a file
	canvas_to_ppm(canvas, "refract_test.ppm");

	// Free allocated memory
	free_canvas(canvas);
	free(floor);
	free(bottom_sphere);
	free(world.shapes);

	return 0;
}