#include "mini_rt.h"

int main()
{
	t_world world;
	t_matrix4x4 *temp, *temp2, *temp3;

	// Initialize the world
	ft_bzero(&world, sizeof(t_world));
	// Allocate memory for the spheres in the world
	world.sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 6);

		// Light source
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));

	// Floor
	t_sphere *floor = (t_sphere *)malloc(sizeof(t_sphere));
	set_transform(floor, scaling_matrix(10, 0.01, 10));
	floor->material = material(create_color(1, 0.9, 0.9), 0.1, 0.9, 0, 200.0);
	floor->radius = 10;
	floor->center = point(0, -10, 0);
	world.sphere[0] = floor;

	// Left wall
	t_sphere *left_wall = (t_sphere *)malloc(sizeof(t_sphere));
	multiply_matrices(temp, translation_matrix(0, 0, 5), rotation_y_matrix(-M_PI / 4));
	multiply_matrices(temp2, temp, rotation_x_matrix(M_PI / 2));
	multiply_matrices(temp3, temp2, scaling_matrix(10, 0.01, 10));
	set_transform(left_wall, temp3);
	left_wall->material = floor->material;
	left_wall->radius = 10;
	left_wall->center = point(0, 0, 5);
	world.sphere[1] = left_wall;

	// Right wall
	t_sphere *right_wall = (t_sphere *)malloc(sizeof(t_sphere));
	multiply_matrices( temp, translation_matrix(0, 0, 5), rotation_y_matrix(M_PI / 4));
	multiply_matrices(temp2, temp, rotation_x_matrix(M_PI / 2));
	multiply_matrices(temp3, temp2, scaling_matrix(10, 0.01, 10));
	set_transform(right_wall, temp3);
	right_wall->material = floor->material;
	right_wall->radius = 10;
	right_wall->center = point(0, 0, 5);
	world.sphere[2] = right_wall;

	// Middle sphere
	t_sphere *middle = (t_sphere *)malloc(sizeof(t_sphere));
	set_transform(middle, translation_matrix(-0.5, 1, 0.5));
	middle->material = material(create_color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0);
	middle->radius = 1;
	middle->center = point(-0.5, 1, 0.5);
	world.sphere[3] = middle;

	// Right sphere
	t_sphere *right = (t_sphere *)malloc(sizeof(t_sphere));
	multiply_matrices( temp, translation_matrix(1.5, 0.5, -0.5), scaling_matrix(0.5, 0.5, 0.5));
	set_transform(right, temp);
	right->material = material(create_color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200.0);
	right->radius = 0.5;
	right->center = point(1.5, 0.5, -0.5);
	world.sphere[4] = right;

	// Left sphere
	t_sphere *left = (t_sphere *)malloc(sizeof(t_sphere));
	multiply_matrices( temp, translation_matrix(-1.5, 0.33, -0.75), scaling_matrix(0.33, 0.33, 0.33));
	set_transform(left, temp);
	left->material = material(create_color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200.0);
	left->radius = 0.33;
	left->center = point(-1.5, 0.33, -0.75);
	world.sphere[5] = left;

	// Camera
	t_camera *camera = create_camera(100, 50, M_PI / 3);
	camera->transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

	// Render the scene
	t_canvas *canvas = render(camera, world);

	// Save the canvas to a file
	canvas_to_ppm(canvas, "scene.ppm");

	// Free allocated memory
	free_canvas(canvas);
	free(floor);
	free(left_wall);
	free(right_wall);
	free(middle);
	free(right);
	free(left);
	free(world.sphere);

	return 0;
}
