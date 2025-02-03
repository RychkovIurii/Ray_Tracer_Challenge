#include "mini_rt.h"
#include <assert.h>

void	test_view_transform_default_orientation()
{
	t_tuple from = point(0, 0, 0);
	t_tuple to = point(0, 0, -1);
	t_tuple up = vector(0, 1, 0);
	t_matrix t = view_transform(from, to, up);
	t_matrix identity = identity_matrix(4);

	assert(is_matrices_equal(t, identity));
	printf("test_view_transform_default_orientation passed\n");
}

void	test_view_transform_positive_z_direction()
{
	t_tuple from = point(0, 0, 0);
	t_tuple to = point(0, 0, 1);
	t_tuple up = vector(0, 1, 0);
	t_matrix t = view_transform(from, to, up);
	t_matrix expected = scaling_matrix(-1, 1, -1);

	assert(is_matrices_equal(t, expected));
	printf("test_view_transform_positive_z_direction passed\n");
}

void	test_view_transform_moves_world()
{
	t_tuple from = point(0, 0, 8);
	t_tuple to = point(0, 0, 0);
	t_tuple up = vector(0, 1, 0);
	t_matrix t = view_transform(from, to, up);
	t_matrix expected = translation_matrix(0, 0, -8);

	assert(is_matrices_equal(t, expected));
	printf("test_view_transform_moves_world passed\n");
}

void	test_view_transform_arbitrary()
{
	t_tuple from = point(1, 3, 2);
	t_tuple to = point(4, -2, 8);
	t_tuple up = vector(1, 1, 0);
	t_matrix t = view_transform(from, to, up);
	t_matrix expected = create_matrix(4);
	expected.matrix[0][0] = -0.50709;
	expected.matrix[0][1] = 0.50709;
	expected.matrix[0][2] = 0.67612;
	expected.matrix[0][3] = -2.36643;
	expected.matrix[1][0] = 0.76772;
	expected.matrix[1][1] = 0.60609;
	expected.matrix[1][2] = 0.12122;
	expected.matrix[1][3] = -2.82843;
	expected.matrix[2][0] = -0.35857;
	expected.matrix[2][1] = 0.59761;
	expected.matrix[2][2] = -0.71714;
	expected.matrix[2][3] = 0.00000;
	expected.matrix[3][0] = 0.00000;
	expected.matrix[3][1] = 0.00000;
	expected.matrix[3][2] = 0.00000;
	expected.matrix[3][3] = 1.00000;

	assert(is_matrices_equal(t, expected));
	printf("test_view_transform_arbitrary passed\n");
}

int main()
{
	test_view_transform_default_orientation();
	test_view_transform_positive_z_direction();
	test_view_transform_moves_world();
	test_view_transform_arbitrary();
	return 0;
}
