#include "mini_rt.h"
#include <assert.h>
/* 
int is_matrices_equal(t_matrix a, t_matrix b)
{
	if (a.size != b.size)
		return 0;
	for (int i = 0; i < a.size; i++)
	{
		for (int j = 0; j < a.size; j++)
		{
			if (fabs(a.matrix[i][j] - b.matrix[i][j]) > 1e-6)
				return 0;
		}
	}
	return 1;
}

int is_materials_equal(t_material a, t_material b)
{
	return (is_tuples_equal(a.color, b.color) &&
			fabs(a.ambient - b.ambient) < 1e-6 &&
			fabs(a.diffuse - b.diffuse) < 1e-6 &&
			fabs(a.specular - b.specular) < 1e-6 &&
			fabs(a.shininess - b.shininess) < 1e-6);
}

void test_default_transformation()
{
	t_object s = create_shape();
	t_matrix identity = identity_matrix(4);
	assert(is_matrices_equal(s.transform, identity));
	printf("✅ test_default_transformation passed\n");
}

void test_assigning_transformation()
{
	t_object s = create_shape();
	t_matrix translation = translation_matrix(2, 3, 4);
	set_transform(&s, translation);
	assert(is_matrices_equal(s.transform, translation));
	printf("✅ test_assigning_transformation passed\n");
}

void test_default_material()
{
	t_object s = create_shape();
	t_material m = default_material();
	assert(is_materials_equal(s.material, m));
	printf("✅ test_default_material passed\n");
}

void test_assigning_material()
{
	t_object s = create_shape();
	t_material m = default_material();
	m.ambient = 1;
	s.material = m;
	assert(is_materials_equal(s.material, m));
	printf("✅ test_assigning_material passed\n");
}

int main()
{
	test_default_transformation();
	test_assigning_transformation();
	test_default_material();
	test_assigning_material();
	return 0;
}

void test_intersecting_scaled_shape_with_ray()
{
	t_object s = create_object();
	set_transform(&s, scaling_matrix(2, 2, 2));
	t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersects xs = intersect(&s, r);
	assert(xs.count == 2);
	printf("✅ test_intersecting_scaled_shape_with_ray passed\n");
}

void test_intersecting_translated_shape_with_ray()
{
	t_object s = create_object();
	set_transform(&s, translation_matrix(5, 0, 0));
	t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersects xs = intersect(&s, r);
	assert(xs.count == 0);
	printf("✅ test_intersecting_translated_shape_with_ray passed\n");
}
 */
