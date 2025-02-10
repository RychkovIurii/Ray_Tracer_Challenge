/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:20:03 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/11 00:15:58 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_world default_world()
{
    t_world world;

    // Allocate memory for shapes
    world.shapes = (t_shape **)calloc(3, sizeof(t_shape *));  // Two spheres + NULL terminator

    // Light Source
    world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

    // First Sphere
    t_shape *sphere1 = (t_shape *)calloc(1, sizeof(t_shape));
    sphere1->type = SHAPE_SPHERE;
    sphere1->transform = identity_matrix(4);
    sphere1->material = material(create_color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0, 0);
    world.shapes[0] = sphere1;

    // Second Sphere (Smaller)
    t_shape *sphere2 = (t_shape *)calloc(1, sizeof(t_shape));
    sphere2->type = SHAPE_SPHERE;
    sphere2->transform = scaling_matrix(0.5, 0.5, 0.5);
    sphere2->material = material(create_color(1, 0, 0), 0.1, 0.7, 0.2, 200.0, 0);
    world.shapes[1] = sphere2;

    return world;
}


t_shape *glass_sphere()
{
    t_shape *s = (t_shape *)calloc(1, sizeof(t_shape));
    s->type = SHAPE_SPHERE;
    s->transform = identity_matrix(4);
    s->material = material(create_color(1, 1, 1), 0.1, 0.9, 0.9, 200.0, 0);
    s->material.transparency = 1.0;      // Fully transparent
    s->material.refractive_index = 1.5;  // Glass refraction index

    return s;
}

void test_glass_sphere()
{
    printf("Running: test_glass_sphere()\n");
    
    t_shape *s = glass_sphere();

    if (!is_matrices_equal(s->transform, identity_matrix(4)))
        printf("❌ Test Failed: glass_sphere() does not have identity transform.\n");
    else if (s->material.transparency != 1.0)
        printf("❌ Test Failed: glass_sphere() does not have correct transparency.\n");
    else if (s->material.refractive_index != 1.5)
        printf("❌ Test Failed: glass_sphere() does not have correct refractive index.\n");
    else
        printf("✅ Test Passed: glass_sphere() is correctly initialized.\n");

    free(s);
}

void test_n1_n2_intersections()
{
    printf("Running: test_n1_n2_intersections()\n");

    // Create the three glass spheres
    t_shape *A = glass_sphere();
    A->transform = scaling_matrix(2, 2, 2);
    A->material.refractive_index = 1.5;

    t_shape *B = glass_sphere();
    B->transform = translation_matrix(0, 0, -0.25);
    B->material.refractive_index = 2.0;

    t_shape *C = glass_sphere();
    C->transform = translation_matrix(0, 0, 0.25);
    C->material.refractive_index = 2.5;

    // Create the world and add the spheres
    t_world world;
    world.shapes = (t_shape **)calloc(4, sizeof(t_shape *));
    world.shapes[0] = A;
    world.shapes[1] = B;
    world.shapes[2] = C;
    world.shapes[3] = NULL;

    // Cast a ray through the center of the spheres
    t_ray r = create_ray(point(0, 0, -4), vector(0, 0, 1));

    // Create the intersections
    t_intersects xs;
    xs.count = 6;
    xs.array = (t_intersection *)malloc(6 * sizeof(t_intersection));
    xs.array[0] = (t_intersection){2, A};
    xs.array[1] = (t_intersection){2.75, B};
    xs.array[2] = (t_intersection){3.25, C};
    xs.array[3] = (t_intersection){4.75, B};
    xs.array[4] = (t_intersection){5.25, C};
    xs.array[5] = (t_intersection){6, A};

    // Check computed values
    double expected_n1[] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
    double expected_n2[] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

    for (int i = 0; i < 6; i++)
    {
        t_intersection comps = prepare_computations(xs.array[i], r, &xs);
        if (fabs(comps.n1 - expected_n1[i]) > 0.0001 || fabs(comps.n2 - expected_n2[i]) > 0.0001)
        {
            printf("❌ Test Failed: Intersection %d expected (%.2f, %.2f) but got (%.2f, %.2f)\n",
                   i, expected_n1[i], expected_n2[i], comps.n1, comps.n2);
            return;
        }
    }

    printf("✅ Test Passed: prepare_computations() correctly determines n1 and n2.\n");

    free(A);
    free(B);
    free(C);
}

void test_under_point()
{
    printf("Running: test_under_point()\n");

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    t_shape *shape = glass_sphere();
    shape->transform = translation_matrix(0, 0, 1);

    t_intersects xs;
    xs.count = 1;
    xs.array = (t_intersection *)malloc(sizeof(t_intersection));
    xs.array[0].t = 5;
    xs.array[0].object = shape;

    t_intersection comps = prepare_computations(xs.array[0], r, &xs);

    if (comps.under_point.z > EPSILON / 2 && comps.point.z < comps.under_point.z)
        printf("✅ Test Passed: under_point is correctly offset.\n");
    else
        printf("❌ Test Failed: under_point is incorrect.\n");

    free(xs.array);
    free(shape);
}

void test_refracted_color_opaque()
{
    printf("Running: test_refracted_color_opaque()\n");

    t_world world = default_world();
    t_shape *shape = world.shapes[0]; // First shape (default sphere)

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_intersects xs;
    xs.count = 2;
    xs.array = (t_intersection *)malloc(2 * sizeof(t_intersection));
    xs.array[0] = (t_intersection){4, shape};
    xs.array[1] = (t_intersection){6, shape};

    t_intersection comps = prepare_computations(xs.array[0], r, &xs);
    t_tuple color = refracted_color(world, comps, 5, NULL);

    if (is_tuples_equal(color, create_color(0, 0, 0)))
        printf("✅ Test Passed: Refracted color for opaque surface is black.\n");
    else
        printf("❌ Test Failed: Expected (0,0,0) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
}

void test_refracted_color_max_depth()
{
    printf("Running: test_refracted_color_max_depth()\n");

    t_world world = default_world();
    t_shape *shape = world.shapes[0]; // First shape

    // Give the shape a glass material
    shape->material.transparency = 1.0;
    shape->material.refractive_index = 1.5;

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_intersects xs;
    xs.count = 2;
    xs.array = (t_intersection *)malloc(2 * sizeof(t_intersection));
    xs.array[0] = (t_intersection){4, shape};
    xs.array[1] = (t_intersection){6, shape};

    t_intersection comps = prepare_computations(xs.array[0], r, &xs);
    t_tuple color = refracted_color(world, comps, 0, NULL);  // Max depth reached

    if (is_tuples_equal(color, create_color(0, 0, 0)))
        printf("✅ Test Passed: Refracted color at max depth is black.\n");
    else
        printf("❌ Test Failed: Expected (0,0,0) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
}

void test_refracted_color_total_internal_reflection()
{
    printf("Running: test_refracted_color_total_internal_reflection()\n");

    t_world world = default_world();
    t_shape *shape = world.shapes[0]; // First shape

    // Give the shape a glass material
    shape->material.transparency = 1.0;
    shape->material.refractive_index = 1.5;

    t_ray r = create_ray(point(0, 0, sqrt(2)/2), vector(0, 1, 0));

    t_intersects xs;
    xs.count = 2;
    xs.array = (t_intersection *)malloc(2 * sizeof(t_intersection));
    xs.array[0] = (t_intersection){-sqrt(2)/2, shape};  // First intersection
    xs.array[1] = (t_intersection){sqrt(2)/2, shape};   // Second intersection (inside sphere)

    t_intersection comps = prepare_computations(xs.array[1], r, &xs);
    t_tuple color = refracted_color(world, comps, 5, NULL);

    if (is_tuples_equal(color, create_color(0, 0, 0)))
        printf("✅ Test Passed: Total internal reflection results in black.\n");
    else
        printf("❌ Test Failed: Expected (0,0,0) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
}

int main()
{
	test_glass_sphere();
	test_n1_n2_intersections();
	test_under_point();
	test_refracted_color_opaque();
	test_refracted_color_max_depth();
	test_refracted_color_total_internal_reflection();
	return 0;
}

/* 
void test_shade_hit_with_transparency();

int main()
{
	t_world world;

	// Allocate memory for the shapes in the world
	world.shapes = (t_shape **)calloc(3, sizeof(t_shape *));

	// 1. Glass Floor
    t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
    floor->center = point(0, 0, 0);
    floor->radius = 0;
    floor->type = SHAPE_PLANE;
    floor->transform = translation_matrix(0, -1, 0);
    floor->material = material(create_color(0.9, 0.9, 0.9), 0.1, 0.9, 0, 200.0, PATTERN_CHECKER);
    floor->material.pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));
    floor->material.pattern.transform = scaling_matrix(0.3, 0.3, 0.3);
    floor->material.reflective = 0.3;
    floor->material.transparency = 0.5;  // Semi-transparent
    floor->material.refractive_index = 1.5;
    world.shapes[0] = floor;


	// 2. Red Sphere Below the Floor
    t_shape *bottom_sphere = (t_shape *)calloc(1, sizeof(t_shape));
    bottom_sphere->center = point(0, 0, 0);
    bottom_sphere->radius = 1;
    bottom_sphere->type = SHAPE_SPHERE;
    bottom_sphere->transform = translation_matrix(0, -3.5, -0.5);
    bottom_sphere->material = material(create_color(1, 0, 0), 0.5, 0.9, 0.3, 200.0, 0);
    bottom_sphere->material.ambient = 0.5;  // Ensure it contributes color
    bottom_sphere->material.transparency = 0.0; // Solid
    bottom_sphere->material.refractive_index = 1.0;
    world.shapes[1] = bottom_sphere;

	// Light source
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));


	// Camera
	t_camera camera = create_camera(400, 200, M_PI / 3);
	camera.transform = view_transform(point(0, 1.5, -5), point(0, 0, 0), vector(0, 1, 0));

	// Render the scene
	t_canvas *canvas = render(camera, world);

	// Save the canvas to a file
	canvas_to_ppm(canvas, "refraction.ppm");

	// Free allocated memory
	free_canvas(canvas);
	free(floor);
	free(bottom_sphere);
	free(world.shapes);
	test_shade_hit_with_transparency();

	return 0;
}

void test_shade_hit_with_transparency()
{
    printf("Running: test_shade_hit_with_transparency()\n");

    // 1. Create a world
    t_world world;
    world.shapes = (t_shape **)calloc(3, sizeof(t_shape *)); // Only floor + sphere

    // 2. Create the glass floor
    t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
    floor->center = point(0, 0, 0);
    floor->radius = 0;
    floor->type = SHAPE_PLANE;
    floor->transform = translation_matrix(0, -1, 0);
    floor->material = material(create_color(0.9, 0.9, 0.9), 0.1, 0.9, 0, 200.0, PATTERN_CHECKER);
    floor->material.transparency = 0.5;  // Semi-transparent
    floor->material.refractive_index = 1.5;
    world.shapes[0] = floor;

    // 3. Create the red sphere below the floor
    t_shape *red_sphere = (t_shape *)calloc(1, sizeof(t_shape));
    red_sphere->center = point(0, 0, 0);
    red_sphere->radius = 1;
    red_sphere->type = SHAPE_SPHERE;
    red_sphere->transform = translation_matrix(0, -3.5, -0.5);
    red_sphere->material = material(create_color(1, 0, 0), 0.5, 0.9, 0.3, 200.0, 0);
    red_sphere->material.ambient = 0.5; // Ensure it contributes color
    red_sphere->material.transparency = 0.0; // Solid
    red_sphere->material.refractive_index = 1.0;
    world.shapes[1] = red_sphere;

    // 4. Light source
    world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

    // 5. Create a ray diagonally toward the floor
    t_ray r = create_ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));

    // 6. Manually create an intersection at t = sqrt(2)
    t_intersects xs;
    xs.count = 1;
    xs.array = (t_intersection *)malloc(sizeof(t_intersection));
    xs.array[0].t = sqrt(2);
    xs.array[0].object = floor; // The glass floor

    // 7. Compute the intersection
    t_intersection comps = prepare_computations(xs.array[0], r, &xs);
    t_tuple color = shade_hit(world, comps, 5, &xs);

    // 8. Expected output (from exercise)
    t_tuple expected_color = create_color(0.93642, 0.68642, 0.68642);

    // 9. Validate the result
    double epsilon = 0.0001;
    if (fabs(color.x - expected_color.x) < epsilon &&
        fabs(color.y - expected_color.y) < epsilon &&
        fabs(color.z - expected_color.z) < epsilon)
		{
			printf("✅ Test Passed! Color matches expected output.\n");
		}
		else
		{
			printf("❌ Test Failed. Expected (%.5f, %.5f, %.5f), but got (%.5f, %.5f, %.5f)\n",
				expected_color.x, expected_color.y, expected_color.z,
				color.x, color.y, color.z);
		}

		// 10. Free memory
		free(xs.array);
		free(floor);
		free(red_sphere);
		free(world.shapes);
	}
 */

/* 	Default values for non-transparent objects:

	transparency = 0.0 (opaque by default)
	refractive_index = 1.0 (air by default) */