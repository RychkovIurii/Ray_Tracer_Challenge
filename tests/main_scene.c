#include "mini_rt.h"

/* t_world *world_new()
{
	t_world	*w = (t_world *)calloc(1, sizeof(t_world));
	return w;
} */

/* t_sphere	sphere(t_material material, t_matrix transform)
{
	t_sphere	s;

	s.center = point(0, 0, 0);
	s.radius = 1.0;
	s.transform = transform;
	s.material = material;
	return (s);
} */

int main()
{
	t_world world;

	// Allocate memory for the spheres in the world
	world.sphere = (t_sphere **)calloc(7, sizeof(t_sphere *));

	// Floor
	t_sphere *floor = (t_sphere *)calloc(1, sizeof(t_sphere));
	floor->center = point(0, 0, 0);
	floor->radius = 1;
	floor->transform = scaling_matrix(10, 0.01, 10);
	//printf("Floor matrix:\n");
	//print_matrix(floor->transform);
	floor->material = material(create_color(1, 0.9, 0.9), 0.1, 0.9, 0, 200.0);
	world.sphere[0] = floor;

	// Left wall
	t_sphere *left_wall = (t_sphere *)calloc(1, sizeof(t_sphere));
	left_wall->center = point(0, 0, 0);
	left_wall->radius = 1;
	t_matrix scal = scaling_matrix(10, 0.01, 10);
	t_matrix rot_x = rotation_x_matrix(M_PI / 2);
	t_matrix rot_y = rotation_y_matrix(-M_PI / 4);
	t_matrix transl = translation_matrix(0, 0, 5);
	left_wall->transform = multiply_matrices(transl, multiply_matrices(rot_y, multiply_matrices(rot_x, scal)));
	//printf("Left wall matrix:\n");
	//print_matrix(left_wall->transform);
	left_wall->material = floor->material;
	world.sphere[1] = left_wall;

	// Right wall
	t_sphere *right_wall = (t_sphere *)calloc(1, sizeof(t_sphere));
	right_wall->center = point(0, 0, 0);
	right_wall->radius = 1;
	t_matrix scal_r = scaling_matrix(10, 0.01, 10);
	t_matrix rot_x_r = rotation_x_matrix(M_PI / 2);
	t_matrix rot_y_r = rotation_y_matrix(M_PI / 4);
	t_matrix transl_r = translation_matrix(0, 0, 5);
	right_wall->transform = multiply_matrices(transl_r, multiply_matrices(rot_y_r, multiply_matrices(rot_x_r, scal_r)));
	//printf("Right wall matrix:\n");
	//print_matrix(right_wall->transform);
	right_wall->material = floor->material;
	world.sphere[2] = right_wall;

	// Middle sphere
	t_sphere *middle = (t_sphere *)calloc(1, sizeof(t_sphere));
	middle->center = point(0, 0, 0);
	middle->radius = 1;
	middle->transform = translation_matrix(-0.5, 1, 0.5);
	//printf("Middle matrix:\n");
	//print_matrix(middle->transform);
	middle->material = material(create_color(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200.0);
	world.sphere[3] = middle;

	// Right sphere
	t_sphere *right = (t_sphere *)calloc(1, sizeof(t_sphere));
	right->center = point(0, 0, 0);
	right->radius = 1;
	right->transform = multiply_matrices(
		translation_matrix(1.5, 0.5, -0.5),
		scaling_matrix(0.5, 0.5, 0.5));
	//printf("Right matrix:\n");
	//print_matrix(right->transform);
	right->material = material(create_color(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200.0);
	world.sphere[4] = right;

	// Left sphere
	t_sphere *left = (t_sphere *)calloc(1, sizeof(t_sphere));
	left->center = point(0, 0, 0);
	left->radius = 1;
	left->transform = multiply_matrices(
		translation_matrix(-1.5, 0.33, -0.75),
		scaling_matrix(0.33, 0.33, 0.33));
	//printf("Left matrix:\n");
	//print_matrix(left->transform);
	left->material = material(create_color(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200.0);
	world.sphere[5] = left;

	// Light source
	world.light = point_light(point(-10, 10, -10), create_color(1, 1, 1));


	// Camera
	t_camera camera = create_camera(300, 150, M_PI / 3);
	camera.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
	//printf("Camera matrix:\n");
	//print_matrix(camera.transform);

	// Render the scene
	t_canvas *canvas = render(camera, world);

	// Save the canvas to a file
	canvas_to_ppm(canvas, "scene3.ppm");

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
