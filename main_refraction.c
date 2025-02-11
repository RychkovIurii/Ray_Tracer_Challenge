/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_refraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:45:41 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/11 12:26:45 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
    t_tuple color = refracted_color(&world, comps, 5, NULL);

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
    t_tuple color = refracted_color(&world, comps, 0, NULL);  // Max depth reached

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
    t_tuple color = refracted_color(&world, comps, 5, NULL);

    if (is_tuples_equal(color, create_color(0, 0, 0)))
        printf("✅ Test Passed: Total internal reflection results in black.\n");
    else
        printf("❌ Test Failed: Expected (0,0,0) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
}

void test_refracted_color_with_refraction()
{
    printf("Running: test_refracted_color_with_refraction()\n");

    t_world world;

	  // Light Source
	  world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

	world.shapes = (t_shape **)calloc(3, sizeof(t_shape *));
    t_shape *A = (t_shape *)calloc(1, sizeof(t_shape));
	A->type = SHAPE_SPHERE;
	A->radius = 1;
	A->center = point(0, 0, 0);
	A->transform = identity_matrix(4);
    A->material.ambient = 1.0; 
	A->material.has_pattern = PATTERN_CHECKER;
    A->material.pattern = stripe_pattern(create_color(1, 1, 1), create_color(0, 0, 0));
	world.shapes[0] = A;

    t_shape *B = (t_shape *)calloc(1, sizeof(t_shape));
	B->type = SHAPE_SPHERE;
	B->radius = 1;
	B->transform = identity_matrix(4);
	B->center= point(0, 0, 0);
    B->material.transparency = 1.0;
    B->material.refractive_index = 1.5;
	world.shapes[1] = B;

    t_ray r = create_ray(point(0, 0, 0.1), vector(0, 1, 0));

    t_intersects xs;
    xs.count = 4;
    xs.array = (t_intersection *)calloc(5 , sizeof(t_intersection));
    xs.array[0] = (t_intersection){-0.9899, A};
    xs.array[1] = (t_intersection){-0.4899, B};
    xs.array[2] = (t_intersection){0.4899, B};  // This is the tested refraction
    xs.array[3] = (t_intersection){0.9899, A};

    t_intersection comps = prepare_computations(xs.array[2], r, &xs);
    t_tuple color = refracted_color(&world, comps, 5, &xs);

    t_tuple expected = create_color(0, 0.99888, 0.04725);

    if (is_tuples_equal(color, expected))
        printf("✅ Test Passed: Refracted color is correct.\n");
    else
        printf("❌ Test Failed: Expected (0,0.99888,0.04725) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
}

void test_shade_hit_with_transparency()
{
    printf("Running: test_shade_hit_with_transparency()\n");

    t_world world;
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));
	world.shapes = (t_shape **)calloc(3, sizeof(t_shape *));

    // ✅ Create the glass floor
    t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
    floor->type = SHAPE_PLANE;
    floor->transform = translation_matrix(0, -1, 0);
    floor->material.transparency = 0.5;
    floor->material.refractive_index = 1.5;
    world.shapes[0] = floor;

    // ✅ Create the red sphere below the floor
    t_shape *red_sphere = (t_shape *)calloc(1, sizeof(t_shape));
    red_sphere->type = SHAPE_SPHERE;
	red_sphere->center = point(0, 0, 0);
	red_sphere->radius = 1;
    red_sphere->transform = translation_matrix(0, -3.0, -0.5);
    red_sphere->material = material(create_color(1, 0, 0), 0.5, 0.9, 0.3, 200.0, 0);
    world.shapes[1] = red_sphere;

    // ✅ Ray diagonally toward the floor
    t_ray r = create_ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));

    // ✅ Intersection with the floor
    t_intersects xs;
    xs.count = 1;
    xs.array = (t_intersection *)calloc(2 , sizeof(t_intersection));
    xs.array[0] = (t_intersection){sqrt(2), floor};

    t_intersection comps = prepare_computations(xs.array[0], r, &xs);
    t_tuple color = shade_hit(&world, comps, 5, &xs);

    t_tuple expected = create_color(0.93642, 0.68642, 0.68642);

    if (is_tuples_equal(color, expected))
        printf("✅ Test Passed: shade_hit() correctly blends refraction and reflection.\n");
    else
        printf("❌ Test Failed: Expected (0.93642, 0.68642, 0.68642) but got (%.5f, %.5f, %.5f)\n", color.x, color.y, color.z);

    free(xs.array);
    free(floor);
    free(red_sphere);
}


int main()
{
    test_refracted_color_opaque();
    test_refracted_color_max_depth();
    test_refracted_color_total_internal_reflection();
	test_refracted_color_with_refraction();
	test_shade_hit_with_transparency();
	return 0;
}

/* 	Default values for non-transparent objects:

	transparency = 0.0 (opaque by default)
	refractive_index = 1.0 (air by default) */