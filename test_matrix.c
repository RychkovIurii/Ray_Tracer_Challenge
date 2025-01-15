#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "tuple.h"

void test_create_matrix()
{
	t_matrix m = create_matrix(3);
	assert(m.size == 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			assert(m.matrix[i][j] == 0);
		}
	}
	free_matrix(m);
	printf("test_create_matrix passed\n");
}

void test_is_matrices_equal()
{
	t_matrix m1 = create_matrix(2);
	t_matrix m2 = create_matrix(2);
	assert(is_matrices_equal(m1, m2) == 1);
	m1.matrix[0][0] = 1;
	assert(is_matrices_equal(m1, m2) == 0);
	free_matrix(m1);
	free_matrix(m2);
	printf("test_is_matrices_equal passed\n");
}

void test_multiply_matrices()
{
	t_matrix m1 = create_matrix(2);
	t_matrix m2 = create_matrix(2);
	m1.matrix[0][0] = 1;
	m1.matrix[1][1] = 1;
	m2.matrix[0][0] = 1;
	m2.matrix[1][1] = 1;
	t_matrix result = multiply_matrices(m1, m2);
	assert(result.matrix[0][0] == 1);
	assert(result.matrix[1][1] == 1);
	free_matrix(m1);
	free_matrix(m2);
	free_matrix(result);
	printf("test_multiply_matrices passed\n");
}

void test_multiply_matrix_by_tuple()
{
	t_matrix m = create_matrix(4);
	t_tuple t = {1, 2, 3, 4};
	t_tuple result = multiply_matrix_by_tuple(m, t);
	assert(result.x == 0);
	assert(result.y == 0);
	assert(result.z == 0);
	assert(result.w == 0);
	free_matrix(m);
	printf("test_multiply_matrix_by_tuple passed\n");
}

void test_multiply_matrix_by_identity_matrix()
{
	t_matrix m = create_matrix(2);
	m.matrix[0][0] = 1;
	m.matrix[1][1] = 1;
	t_matrix result = multiply_matrix_by_identity_matrix(m);
	assert(result.matrix[0][0] == 1);
	assert(result.matrix[1][1] == 1);
	free_matrix(m);
	free_matrix(result);
	printf("test_multiply_matrix_by_identity_matrix passed\n");
}

void test_multiply_identity_matrix_by_tuple()
{
	t_tuple t = {1, 2, 3, 4};
	t_tuple result = multiply_identity_matrix_by_tuple(t);
	assert(result.x == 1);
	assert(result.y == 2);
	assert(result.z == 3);
	assert(result.w == 4);
	printf("test_multiply_identity_matrix_by_tuple passed\n");
}

void test_transpose_matrix()
{
	t_matrix a = create_matrix(2);
	a.matrix[0][0] = 1;
	a.matrix[0][1] = 2;
	a.matrix[1][0] = 3;
	a.matrix[1][1] = 4;

	t_matrix expected = create_matrix(2);
	expected.matrix[0][0] = 1;
	expected.matrix[0][1] = 3;
	expected.matrix[1][0] = 2;
	expected.matrix[1][1] = 4;

	t_matrix result = transpose_matrix(a);
	assert(is_matrices_equal(result, expected) && "Matrices are not equal");
	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_transpose_matrix passed\n");
}

int main()
{
	test_create_matrix();
	test_is_matrices_equal();
	test_multiply_matrices();
	test_multiply_matrix_by_tuple();
	test_multiply_matrix_by_identity_matrix();
	test_multiply_identity_matrix_by_tuple();
	test_transpose_matrix();
	printf("All tests passed!\n");
	return (0);
}