/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:43:45 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/12 22:36:31 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"
/* 
Common materials and their refractive indices:

Vacuum: 1
Air: 1.00029
Water: 1.333
Glass: 1.52
Diamond: 2.417
 */

/* int main()
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
    //t_camera camera = create_camera(200, 100, M_PI / 3);
    //camera.transform = view_transform(point(0, 5, -10), point(0, 0, 0), vector(0, 1, 0));

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
} */

#include "mini_rt.h"  // Assumes you have definitions for point(), vector(), create_color(), 
                       // translation_matrix(), scaling_matrix(), rotation_x_matrix(), 
                       // rotation_y_matrix(), rotation_z_matrix(), multiply_matrices(), 
                       // view_transform(), create_camera(), point_light(), material(), 
                       // checkers_pattern(), stripe_pattern(), etc.

int main(void)
{
    t_world world;
    // There are 13 objects:
    //  0: Floor
    //  1: Ceiling
    //  2: West wall
    //  3: East wall
    //  4: North wall
    //  5: South wall
    //  6: Background sphere 1
    //  7: Background sphere 2
    //  8: Background sphere 3
    //  9: Background sphere 4
    // 10: Red foreground sphere
    // 11: Blue glass sphere
    // 12: Green glass sphere
    world.shapes = (t_shape **)calloc(14, sizeof(t_shape *));

    /* ---------------------------------------------------------
       CAMERA (from YAML):
         width: 400, height: 200, field-of-view: 1.152
         from: [-2.6, 1.5, -3.9]
         to:   [-0.6, 1, -0.8]
         up:   [0, 1, 0]
    --------------------------------------------------------- */
    t_camera camera = create_camera(600, 300, 1.152);
    camera.transform = view_transform(
        point(-2.6, 1.5, -3.9),  // camera position ("from")
        point(-0.6, 1, -0.8),     // look-at point ("to")
        vector(0, 1, 0)          // up vector
    );

    /* ---------------------------------------------------------
       LIGHT (from YAML):
         at: [-4.9, 4.9, -1]
         intensity: [1, 1, 1]
    --------------------------------------------------------- */
    world.light = point_light(point(-4.9, 4.9, -1), create_color(1, 1, 1));

    /* ---------------------------------------------------------
       Define constant: wall-material 
       YAML specifies:
         pattern: stripes with colors [0.45,0.45,0.45] and [0.55,0.55,0.55]
         pattern.transform: scale(0.25,0.25,0.25) then rotate-y(1.5708)
         ambient: 0, diffuse: 0.4, specular: 0, reflective: 0.3
    --------------------------------------------------------- */
    t_material wall_material = material(create_color(1, 1, 1), /*dummy color*/
                                          0,      /* ambient */
                                          0.4,    /* diffuse */
                                          0,      /* specular */
                                          200.0,  /* shininess (default) */
                                          PATTERN_STRIPE);
    wall_material.pattern = stripe_pattern(
        create_color(0.45, 0.45, 0.45),
        create_color(0.55, 0.55, 0.55)
    );
    wall_material.pattern.transform = multiply_matrices(
        scaling_matrix(0.25, 0.25, 0.25),
        rotation_y_matrix(1.5708)
    );
    wall_material.reflective = 0.3;

    /* ---------------------------------------------------------
       Floor: checkered floor
       YAML:
         transform: rotate-y(0.31415)
         material: pattern checkers with colors [0.35,0.35,0.35] and [0.65,0.65,0.65]
                   specular: 0, reflective: 0.4
    --------------------------------------------------------- */
    t_shape *floor = (t_shape *)calloc(1, sizeof(t_shape));
    floor->type = SHAPE_PLANE;
    floor->transform = rotation_y_matrix(0.31415);
    // Using a checkers pattern for the floor material:
    floor->material = material(create_color(0,0,0),  /* color not used */
                                 0.1,          /* ambient (if needed) */
                                 0.9,          /* diffuse (if needed) */
                                 0,            /* specular */
                                 200.0,        /* shininess */
                                 PATTERN_CHECKER);
    floor->material.pattern = stripe_pattern(
        create_color(0.35, 0.35, 0.35),
        create_color(0.65, 0.65, 0.65)
    );
    floor->material.reflective = 0.4;
    world.shapes[0] = floor;

    /* ---------------------------------------------------------
       Ceiling:
       YAML:
         transform: translate(0, 5, 0)
         material: color [0.8,0.8,0.8], ambient: 0.3, specular: 0
    --------------------------------------------------------- */
    t_shape *ceiling = (t_shape *)calloc(1, sizeof(t_shape));
    ceiling->type = SHAPE_PLANE;
    ceiling->transform = translation_matrix(0, 5, 0);
    ceiling->material = material(create_color(0.8, 0.8, 0.8),
                                   0.3,   /* ambient */
                                   0.7,   /* diffuse (assumed) */
                                   0,     /* specular */
                                   200.0, /* shininess */
                                   PATTERN_NONE);
    world.shapes[1] = ceiling;

    /* ---------------------------------------------------------
       Walls: West, East, North, South – all use wall_material.
       Their transforms are defined as follows in YAML:

       West wall:
         transform: rotate-y(1.5708), rotate-z(1.5708), translate(-5,0,0)
       East wall:
         transform: rotate-y(1.5708), rotate-z(1.5708), translate(5,0,0)
       North wall:
         transform: rotate-x(1.5708), translate(0,0,5)
       South wall:
         transform: rotate-x(1.5708), translate(0,0,-5)
       (Note: Adjust multiplication order as required by your math library.)
    --------------------------------------------------------- */
    // West wall
    t_shape *west_wall = (t_shape *)calloc(1, sizeof(t_shape));
    west_wall->type = SHAPE_PLANE;
    {
        t_matrix r_y = rotation_y_matrix(1.5708);
        t_matrix r_z = rotation_z_matrix(1.5708);
        t_matrix t = translation_matrix(-5, 0, 0);
        // Apply rotations then translation:
        t_matrix rot = multiply_matrices(r_z, r_y);
        west_wall->transform = multiply_matrices(t, rot);
    }
    west_wall->material = wall_material;
    world.shapes[2] = west_wall;

    // East wall
    t_shape *east_wall = (t_shape *)calloc(1, sizeof(t_shape));
    east_wall->type = SHAPE_PLANE;
    {
        t_matrix r_y = rotation_y_matrix(1.5708);
        t_matrix r_z = rotation_z_matrix(1.5708);
        t_matrix t = translation_matrix(5, 0, 0);
        t_matrix rot = multiply_matrices(r_z, r_y);
        east_wall->transform = multiply_matrices(t, rot);
    }
    east_wall->material = wall_material;
    world.shapes[3] = east_wall;

    // North wall
    t_shape *north_wall = (t_shape *)calloc(1, sizeof(t_shape));
    north_wall->type = SHAPE_PLANE;
    {
        t_matrix ro_x = rotation_x_matrix(1.5708);
        t_matrix tr = translation_matrix(0, 0, 5);
        north_wall->transform = multiply_matrices(tr, ro_x);
    }
    north_wall->material = wall_material;
    world.shapes[4] = north_wall;

    // South wall
    t_shape *south_wall = (t_shape *)calloc(1, sizeof(t_shape));
    south_wall->type = SHAPE_PLANE;
    {
        t_matrix rot_x = rotation_x_matrix(1.5708);
        t_matrix tra = translation_matrix(0, 0, -5);
        south_wall->transform = multiply_matrices(tra, rot_x);
    }
    south_wall->material = wall_material;
    world.shapes[5] = south_wall;

    /* ---------------------------------------------------------
       Background Spheres:
         1. Scale(0.4,0.4,0.4) then translate(4.6, 0.4, 1)
            color: [0.8, 0.5, 0.3], shininess: 50
         2. Scale(0.3,0.3,0.3) then translate(4.7, 0.3, 0.4)
            color: [0.9, 0.4, 0.5], shininess: 50
         3. Scale(0.5,0.5,0.5) then translate(-1, 0.5, 4.5)
            color: [0.4, 0.9, 0.6], shininess: 50
         4. Scale(0.3,0.3,0.3) then translate(-1.7, 0.3, 4.7)
            color: [0.4, 0.6, 0.9], shininess: 50
    --------------------------------------------------------- */
    // Background sphere 1
    t_shape *bg_sphere1 = (t_shape *)calloc(1, sizeof(t_shape));
    bg_sphere1->center = point(0, 0, 0);
    bg_sphere1->radius = 1;
    bg_sphere1->type = SHAPE_SPHERE;
    {
        t_matrix s = scaling_matrix(0.4, 0.4, 0.4);
        t_matrix tran = translation_matrix(4.6, 0.4, 1);
        bg_sphere1->transform = multiply_matrices(tran, s);
    }
    bg_sphere1->material = material(create_color(0.8, 0.5, 0.3),
                                      0.1, 0.9, 0.0, 50.0, PATTERN_NONE);
    bg_sphere1->material.shininess = 50;
    world.shapes[6] = bg_sphere1;

    // Background sphere 2
    t_shape *bg_sphere2 = (t_shape *)calloc(1, sizeof(t_shape));
    bg_sphere2->center = point(0, 0, 0);
    bg_sphere2->radius = 1;
    bg_sphere2->type = SHAPE_SPHERE;
    {
        t_matrix sc = scaling_matrix(0.3, 0.3, 0.3);
        t_matrix trans = translation_matrix(4.7, 0.3, 0.4);
        bg_sphere2->transform = multiply_matrices(trans, sc);
    }
    bg_sphere2->material = material(create_color(0.9, 0.4, 0.5),
                                      0.1, 0.9, 0.0, 50.0, PATTERN_NONE);
    bg_sphere2->material.shininess = 50;
    world.shapes[7] = bg_sphere2;

    // Background sphere 3
    t_shape *bg_sphere3 = (t_shape *)calloc(1, sizeof(t_shape));
    bg_sphere3->center = point(0, 0, 0);
    bg_sphere3->radius = 1;
    bg_sphere3->type = SHAPE_SPHERE;
    {
        t_matrix s = scaling_matrix(0.5, 0.5, 0.5);
        t_matrix t = translation_matrix(-1, 0.5, 4.5);
        bg_sphere3->transform = multiply_matrices(t, s);
    }
    bg_sphere3->material = material(create_color(0.4, 0.9, 0.6),
                                      0.1, 0.9, 0.0, 50.0, PATTERN_NONE);
    bg_sphere3->material.shininess = 50;
    world.shapes[8] = bg_sphere3;

    // Background sphere 4
    t_shape *bg_sphere4 = (t_shape *)calloc(1, sizeof(t_shape));
    bg_sphere4->center = point(0, 0, 0);
    bg_sphere4->radius = 1;
    bg_sphere4->type = SHAPE_SPHERE;
    {
        t_matrix s = scaling_matrix(0.3, 0.3, 0.3);
        t_matrix t = translation_matrix(-1.7, 0.3, 4.7);
        bg_sphere4->transform = multiply_matrices(t, s);
    }
    bg_sphere4->material = material(create_color(0.4, 0.6, 0.9),
                                      0.1, 0.9, 0.0, 50.0, PATTERN_NONE);
    bg_sphere4->material.shininess = 50;
    world.shapes[9] = bg_sphere4;

    /* ---------------------------------------------------------
       Foreground Spheres:
         Red sphere:
           transform: translate(-0.6, 1, 0.6)
           color: [1, 0.3, 0.2], specular: 0.4, shininess: 5
         Blue glass sphere:
           transform: scale(0.7,0.7,0.7) then translate(0.6, 0.7, -0.6)
           color: [0,0,0.2], ambient: 0, diffuse: 0.4, specular: 0.9,
           shininess: 300, reflective: 0.9, transparency: 0.9, refractive-index: 1.5
         Green glass sphere:
           transform: scale(0.5,0.5,0.5) then translate(-0.7, 0.5, -0.8)
           color: [0,0.2,0], ambient: 0, diffuse: 0.4, specular: 0.9,
           shininess: 300, reflective: 0.9, transparency: 0.9, refractive-index: 1.5
    --------------------------------------------------------- */
    // Red foreground sphere
    t_shape *fg_red = (t_shape *)calloc(1, sizeof(t_shape));
    fg_red->center = point(0, 0, 0);
    fg_red->radius = 1;
    fg_red->type = SHAPE_SPHERE;
    fg_red->transform = translation_matrix(-0.6, 1, 0.6);
    fg_red->material = material(create_color(1, 0.3, 0.2),
                                  0.1, 0.9, 0.4, 5.0, PATTERN_NONE);
    world.shapes[10] = fg_red;

    // Blue glass sphere
    t_shape *fg_blue = (t_shape *)calloc(1, sizeof(t_shape));
    fg_blue->center = point(0, 0, 0);
    fg_blue->radius = 1;
    fg_blue->type = SHAPE_SPHERE;
    {
        t_matrix s = scaling_matrix(0.7, 0.7, 0.7);
        t_matrix t = translation_matrix(0.6, 0.7, -0.6);
        fg_blue->transform = multiply_matrices(t, s);
    }
    fg_blue->material = material(create_color(0, 0, 0.2),
                                   0,      /* ambient */
                                   0.1,    /* diffuse */
                                   0.2,    /* specular */
                                   300.0,  /* shininess */
                                   PATTERN_NONE);
    fg_blue->material.reflective = 0.9;
    fg_blue->material.transparency = 0.9;
    fg_blue->material.refractive_index = 1.5;
    world.shapes[11] = fg_blue;

    // Green glass sphere
    t_shape *fg_green = (t_shape *)calloc(1, sizeof(t_shape));
    fg_green->center = point(0, 0, 0);
    fg_green->radius = 1;
    fg_green->type = SHAPE_SPHERE;
    {
        t_matrix s = scaling_matrix(0.5, 0.5, 0.5);
        t_matrix t = translation_matrix(-0.7, 0.5, -0.8);
        fg_green->transform = multiply_matrices(t, s);
    }
    fg_green->material = material(create_color(0, 0.2, 0),
                                    0,      /* ambient */
                                    0.4,    /* diffuse */
                                    0.9,    /* specular */
                                    300.0,  /* shininess */
                                    PATTERN_NONE);
    fg_green->material.reflective = 0.9;
    fg_green->material.transparency = 0.9;
    fg_green->material.refractive_index = 1.5;
    world.shapes[12] = fg_green;

    /* ---------------------------------------------------------
       RENDER THE SCENE
    --------------------------------------------------------- */
    t_canvas *canvas = render(camera, &world);
    canvas_to_ppm(canvas, "rendered_scene.ppm");

    /* ---------------------------------------------------------
       FREE ALLOCATED MEMORY
    --------------------------------------------------------- */
    free_canvas(canvas);
    for (int i = 0; i < 13; i++) {
        free(world.shapes[i]);
    }
    free(world.shapes);

    return 0;
}
