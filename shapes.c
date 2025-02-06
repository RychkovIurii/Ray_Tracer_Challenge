/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:20:14 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/06 23:28:34 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_material default_material()
{
	t_material mat;
	mat.color = create_color(1, 1, 1);
	mat.ambient = 0.1;
	mat.diffuse = 0.9;
	mat.specular = 0.9;
	mat.shininess = 200.0;
	return (mat);
}

void free_intersects(t_intersects *xs)
{
    if (xs->array)
        free(xs->array);
    xs->array = NULL;
    xs->count = 0;
}

t_matrix identity_matrix(int size)
{
	t_matrix id = create_matrix(size);
	for (int i = 0; i < size; i++)
		id.matrix[i][i] = 1;
	return id;
}

/* typedef struct s_object {
	t_matrix	transform;
	t_material	material;
}				t_object;

typedef struct s_sphere {
	t_object	base;
	t_tuple		center;
	double		radius;
}				t_sphere; */

/* t_object create_object()
{
	t_object shape;
	shape.transform = identity_matrix(4);
	shape.material = default_material();
	return (shape);
} */

t_shape create_shape(t_shape_type type)
{
	t_shape	shape;

	shape.transform = identity_matrix(4);
	shape.material = default_material();
	shape.type = type;
	shape.center = point(0, 0, 0);
	shape.radius = 1;
	return (shape);
}

t_sphere create_sphere()
{
	t_sphere	sphere;

	sphere.base = create_shape(SHAPE_SPHERE);
	sphere.center = point(0, 0, 0);
	sphere.radius = 1;
	return (sphere);
}

void set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
}

/* t_intersects local_intersect(t_shape *shape, t_ray ray)
{
	t_sphere *sphere = (t_sphere *)shape;
	t_intersects result;
	t_tuple sphere_to_ray;
	double a, b, c, discriminant;

	sphere_to_ray = substract_tuple(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		result.count = 0;
		result.array = NULL;
		return result;
	}

	result.count = 2;
	result.array = (t_intersection *)calloc(2, sizeof(t_intersection));
	result.array[0].t = (-b - sqrt(discriminant)) / (2 * a);
	result.array[0].object = shape;
	result.array[1].t = (-b + sqrt(discriminant)) / (2 * a);
	result.array[1].object = shape;

	return result;
} */

t_intersects local_intersect_sphere(t_shape *sphere, t_ray transformed_ray)
{
	t_intersects result;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_intersection	intersection1;
	t_intersection	intersection2;

	sphere_to_ray = substract_tuple(transformed_ray.origin, sphere->center);
	printf("sphere_to_ray: (%f, %f, %f, %f)\n", 
       sphere_to_ray.x, sphere_to_ray.y, sphere_to_ray.z, sphere_to_ray.w);
	a = dot(transformed_ray.direction, transformed_ray.direction);
	b = 2 * dot(transformed_ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	printf("Computed values: a=%f, b=%f, c=%f, discriminant=%f\n", a, b, c, discriminant);

	if (discriminant < 0) {
		result.count = 0;
		result.array = NULL;
		return result;
	}

	result.count = 2;
	result.array = (t_intersection *)calloc(2, sizeof(t_intersection));
	result.array[0].t = (-b - sqrt(discriminant)) / (2 * a);
	result.array[0].object = sphere;
	result.array[1].t = (-b + sqrt(discriminant)) / (2 * a);
	result.array[1].object = sphere;

	return result;
}

/* t_intersects intersect(t_object *shape, t_ray ray)
{
	t_ray local_ray;

	local_ray = transform_ray(ray, inverse_matrix(shape->transform));
	return (local_intersect(shape, local_ray));
} */

t_intersects intersect(t_shape *shape, t_ray ray)
{
	t_ray local_ray;

	local_ray = transform_ray(ray, inverse_matrix(shape->transform));
	printf("🔍 Checking shape type: %d\n", shape->type);

	shape->saved_ray = local_ray;
	/* printf("Original Ray: Origin(%f, %f, %f), Dir(%f, %f, %f)\n",
       ray.origin.x, ray.origin.y, ray.origin.z,
       ray.direction.x, ray.direction.y, ray.direction.z);
	printf("Transformed Ray: Origin(%f, %f, %f), Dir(%f, %f, %f)\n",
       local_ray.origin.x, local_ray.origin.y, local_ray.origin.z,
       local_ray.direction.x, local_ray.direction.y, local_ray.direction.z); */
	if (shape->type == SHAPE_SPHERE)
	{
		printf("✅ This object is a sphere!\n");
		return local_intersect_sphere(shape, local_ray);
	}
	 printf("⚠️ Warning: Unknown shape type in intersect()!\n");

	return (t_intersects){0, NULL};  // No intersections for unknown shapes
}

t_tuple local_normal_at_sphere(t_tuple sphere_center, t_tuple local_point)
{
	/* printf("sphere->center: (%f, %f, %f, %f)\n", 
	   sphere->center.x, sphere->center.y, sphere->center.z, sphere->center.w); */
	return (substract_tuple(local_point, sphere_center));
}

t_tuple	normal_at(t_shape *shape, t_tuple world_point)
{
	t_tuple surface_normal;
	t_tuple world_normal;
	t_tuple local_point;
	t_tuple local_normal;
	t_matrix inverse_transform;

	inverse_transform = inverse_matrix(shape->transform);
	local_point = multiply_matrix_by_tuple(inverse_transform, world_point);
	if (shape->type == SHAPE_SPHERE)
	{
		printf("🔍 Calculating normal for sphere\n");
		local_normal = local_normal_at_sphere(shape->center, local_point);
	}
	world_normal = multiply_matrix_by_tuple(transpose_matrix(inverse_transform), local_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}


#include <assert.h>

int is_materials_equal(t_material a, t_material b)
{
	return (is_tuples_equal(a.color, b.color) &&
			fabs(a.ambient - b.ambient) < 1e-6 &&
			fabs(a.diffuse - b.diffuse) < 1e-6 &&
			fabs(a.specular - b.specular) < 1e-6 &&
			fabs(a.shininess - b.shininess) < 1e-6);
}

t_shape test_shape() {
	return create_shape(SHAPE_SPHERE);
}

void test_default_transformation() {
	t_shape s = test_shape();
	assert(is_matrices_equal(s.transform, identity_matrix(4)));
	printf("✅ test_default_transformation passed\n");
}

void test_assigning_transformation() {
	t_shape s = test_shape();
	t_matrix translation = translation_matrix(2, 3, 4);
	set_transform(&s, translation);
	assert(is_matrices_equal(s.transform, translation));
	printf("✅ test_assigning_transformation passed\n");
}

void test_default_material() {
	t_shape s = test_shape();
	t_material m = default_material();
	assert(is_materials_equal(s.material, m));
	printf("✅ test_default_material passed\n");
}

void test_assigning_material() {
	t_shape s = test_shape();
	t_material m = default_material();
	m.ambient = 1;
	s.material = m;
	assert(is_materials_equal(s.material, m));
	printf("✅ test_assigning_material passed\n");
}

void test_normal_on_translated_shape()
{
    t_shape s = test_shape();
    set_transform(&s, translation_matrix(0, 1, 0));

    t_tuple n = normal_at(&s, point(0, 1.70711, -0.70711));

    assert(is_tuples_equal(n, vector(0, 0.70711, -0.70711)));
    printf("✅ test_normal_on_translated_shape passed\n");
}

void test_normal_on_transformed_shape()
{
    t_shape s = test_shape();
    
    // Transformation: Scaling (1, 0.5, 1) then rotating around Z-axis by π/5
    t_matrix m = multiply_matrices(scaling_matrix(1, 0.5, 1), rotation_z_matrix(M_PI / 5));
    set_transform(&s, m);

    t_tuple n = normal_at(&s, point(0, sqrt(2) / 2, -sqrt(2) / 2));

    assert(is_tuples_equal(n, vector(0, 0.97014, -0.24254)));
    printf("✅ test_normal_on_transformed_shape passed\n");
}

void test_intersecting_scaled_shape_with_ray()
{
    t_shape s = test_shape();
    set_transform(&s, scaling_matrix(2, 2, 2));

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersects xs = intersect(&s, r);

    assert(xs.count == 2);
    assert(is_tuples_equal(xs.array[0].object->saved_ray.origin, point(0, 0, -2.5)));
    assert(is_tuples_equal(xs.array[0].object->saved_ray.direction, vector(0, 0, 0.5)));

    free_intersects(&xs);
    printf("✅ test_intersecting_scaled_shape_with_ray passed\n");
}

void test_intersecting_translated_shape_with_ray()
{
    t_shape s = test_shape();
    set_transform(&s, translation_matrix(5, 0, 0));

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersects xs = intersect(&s, r);

    assert(xs.count == 0); // The ray does not hit the translated shape

    printf("✅ test_intersecting_translated_shape_with_ray passed\n");
}





int main()
{
	test_default_transformation();
	test_assigning_transformation();
	test_default_material();
	test_assigning_material();
	test_normal_on_translated_shape();
	test_normal_on_transformed_shape();
	test_intersecting_scaled_shape_with_ray();
	test_intersecting_translated_shape_with_ray();
	return 0;
}
