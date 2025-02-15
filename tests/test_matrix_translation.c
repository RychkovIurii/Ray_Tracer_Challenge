#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "tuple.h"

// Test function for multiplying by a translation matrix
void test_multiplying_by_translation_matrix()
{
	t_matrix transform = translation_matrix(5, -3, 2);
	t_tuple p = point(-3, 4, 5);
	t_tuple expected = point(2, 1, 7);
	t_tuple result = multiply_matrix_by_tuple(transform, p);
	assert(is_tuples_equal(result, expected) && "test_multiplying_by_translation_matrix failed");
	free_matrix(transform);
	printf("test_multiplying_by_translation_matrix passed\n");
}

// Test function for multiplying by the inverse of a translation matrix
void test_multiplying_by_inverse_translation_matrix()
{
	t_matrix transform = translation_matrix(5, -3, 2);
	t_matrix inv = inverse_matrix(transform);
	t_tuple p = point(-3, 4, 5);
	t_tuple expected = point(-8, 7, 3);
	t_tuple result = multiply_matrix_by_tuple(inv, p);
	assert(is_tuples_equal(result, expected) && "test_multiplying_by_inverse_translation_matrix failed");
	free_matrix(transform);
	free_matrix(inv);
	printf("test_multiplying_by_inverse_translation_matrix passed\n");
}

// Test function for translation not affecting vectors
void test_translation_does_not_affect_vectors()
{
	t_matrix transform = translation_matrix(5, -3, 2);
	t_tuple v = vector(-3, 4, 5);
	t_tuple result = multiply_matrix_by_tuple(transform, v);
	assert(is_tuples_equal(result, v) && "test_translation_does_not_affect_vectors failed");
	free_matrix(transform);
	printf("test_translation_does_not_affect_vectors passed\n");
}

// Test function scaling_matrix
void test_scaling_by_negative_value()
{
	t_matrix transform = scaling_matrix(-1, 1, 1);
	t_tuple p = point(2, 3, 4);
	t_tuple expected = point(-2, 3, 4);
	t_tuple result = multiply_matrix_by_tuple(transform, p);
	assert(is_tuples_equal(result, expected) && "test_scaling_by_negative_value failed");
	free_matrix(transform);
	printf("test_scaling_by_negative_value passed\n");
}


// Test function rotation_x_matrix
void test_rotation_point_axe_x()
{
	t_tuple p = point(0, 1, 0);
	t_matrix half_quarter = rotation_x_matrix(M_PI / 4);
	t_matrix full_quarter = rotation_x_matrix(M_PI / 2);
	t_tuple expected_half_quarter = point(0, sqrt(2) / 2, sqrt(2) / 2);
	t_tuple expected_full_quarter = point(0, 0, 1);
	t_tuple result_half_quarter = multiply_matrix_by_tuple(half_quarter, p);
	t_tuple result_full_quarter = multiply_matrix_by_tuple(full_quarter, p);
	assert(is_tuples_equal(result_half_quarter, expected_half_quarter) && "test_rotation_point_axe_x failed");
	assert(is_tuples_equal(result_full_quarter, expected_full_quarter) && "test_rotation_point_axe_x failed");
	free_matrix(half_quarter);
	free_matrix(full_quarter);
	printf("test_rotation_point_axe_x passed\n");
}

// Test function rotation_y_matrix
void test_rotation_point_axe_y()
{
	t_tuple p = point(0, 0, 1);
	t_matrix half_quarter = rotation_y_matrix(M_PI / 4);
	t_matrix full_quarter = rotation_y_matrix(M_PI / 2);
	t_tuple expected_half_quarter = point(sqrt(2) / 2, 0, sqrt(2) / 2);
	t_tuple expected_full_quarter = point(1, 0, 0);
	t_tuple result_half_quarter = multiply_matrix_by_tuple(half_quarter, p);
	t_tuple result_full_quarter = multiply_matrix_by_tuple(full_quarter, p);
	assert(is_tuples_equal(result_half_quarter, expected_half_quarter) && "test_rotation_point_axe_y failed");
	assert(is_tuples_equal(result_full_quarter, expected_full_quarter) && "test_rotation_point_axe_y failed");
	free_matrix(half_quarter);
	free_matrix(full_quarter);
	printf("test_rotation_point_axe_y passed\n");
}

// Test function rotation_z_matrix
void test_rotation_point_axe_z()
{
	t_tuple p = point(0, 1, 0);
	t_matrix half_quarter = rotation_z_matrix(M_PI / 4);
	t_matrix full_quarter = rotation_z_matrix(M_PI / 2);
	t_tuple expected_half_quarter = point(-sqrt(2) / 2, sqrt(2) / 2, 0);
	t_tuple expected_full_quarter = point(-1, 0, 0);
	t_tuple result_half_quarter = multiply_matrix_by_tuple(half_quarter, p);
	t_tuple result_full_quarter = multiply_matrix_by_tuple(full_quarter, p);
	assert(is_tuples_equal(result_half_quarter, expected_half_quarter) && "test_rotation_point_axe_z failed");
	assert(is_tuples_equal(result_full_quarter, expected_full_quarter) && "test_rotation_point_axe_z failed");
	free_matrix(half_quarter);
	free_matrix(full_quarter);
	printf("test_rotation_point_axe_z passed\n");
}

// Tet function for shearing_matrix
void test_shearing_matrix()
{
	t_matrix transform = shearing_matrix(1, 0, 0, 0, 0, 0);
	t_tuple p = point(2, 3, 4);
	t_tuple expected = point(5, 3, 4);
	t_tuple result = multiply_matrix_by_tuple(transform, p);
	assert(is_tuples_equal(result, expected) && "test_shearing_matrix failed");
	free_matrix(transform);
	printf("test_shearing_matrix passed\n");
}

//Test individual transformations are applied in sequence
void test_individual_transformations()
{
	t_tuple p = point(1, 0, 1);
	t_matrix A = rotation_x_matrix(M_PI / 2);
	t_matrix B = scaling_matrix(5, 5, 5);
	t_matrix C = translation_matrix(10, 5, 7);
	t_tuple p2 = multiply_matrix_by_tuple(A, p);
	t_tuple p3 = multiply_matrix_by_tuple(B, p2);
	t_tuple p4 = multiply_matrix_by_tuple(C, p3);
	t_tuple expected = point(15, 0, 7);
	assert(is_tuples_equal(p4, expected) && "test_individual_transformations failed");
	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	printf("test_individual_transformations passed\n");
}

//Test chained transformations must be applied in reverse order
void test_chained_transformations()
{
	t_tuple p = point(1, 0, 1);
	t_matrix A = rotation_x_matrix(M_PI / 2);
	t_matrix B = scaling_matrix(5, 5, 5);
	t_matrix C = translation_matrix(10, 5, 7);
	t_matrix T = multiply_matrices(C, multiply_matrices(B, A));
	t_tuple result = multiply_matrix_by_tuple(T, p);
	t_tuple expected = point(15, 0, 7);
	assert(is_tuples_equal(result, expected) && "test_chained_transformations failed");
	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(T);
	printf("test_chained_transformations passed\n");
}

int main()
{
	test_multiplying_by_translation_matrix();
	test_multiplying_by_inverse_translation_matrix();
	test_translation_does_not_affect_vectors();
	test_scaling_by_negative_value();
	test_rotation_point_axe_x();
	test_rotation_point_axe_y();
	test_rotation_point_axe_z();
	test_shearing_matrix();
	test_individual_transformations();
	test_chained_transformations();
	printf("All tests passed!\n");
	return 0;
}