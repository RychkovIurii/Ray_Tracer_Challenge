#include <assert.h>
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

int main()
{
	test_multiplying_by_translation_matrix();
	test_multiplying_by_inverse_translation_matrix();
	test_translation_does_not_affect_vectors();
	printf("All tests passed!\n");
	return 0;
}