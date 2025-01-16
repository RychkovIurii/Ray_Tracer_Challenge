#include <assert.h>
#include <stdio.h>
#include "matrix.h"

// Test function for submatrix of a 3x3 matrix
void test_submatrix_3x3()
{
	t_matrix a = create_matrix(3);
	a.matrix[0][0] = 1; a.matrix[0][1] = 5; a.matrix[0][2] = 0;
	a.matrix[1][0] = -3; a.matrix[1][1] = 2; a.matrix[1][2] = 7;
	a.matrix[2][0] = 0; a.matrix[2][1] = 6; a.matrix[2][2] = -3;

	t_matrix expected = create_matrix(2);
	expected.matrix[0][0] = -3; expected.matrix[0][1] = 2;
	expected.matrix[1][0] = 0; expected.matrix[1][1] = 6;

	t_matrix result = submatrix(a, 0, 2);
	assert(is_matrices_equal(result, expected) && "test_submatrix_3x3 failed");

	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_submatrix_3x3 passed\n");
}

// Test function for submatrix of a 4x4 matrix
void test_submatrix_4x4()
{
	t_matrix a = create_matrix(4);
	a.matrix[0][0] = -6; a.matrix[0][1] = 1; a.matrix[0][2] = 1; a.matrix[0][3] = 6;
	a.matrix[1][0] = -8; a.matrix[1][1] = 5; a.matrix[1][2] = 8; a.matrix[1][3] = 6;
	a.matrix[2][0] = -1; a.matrix[2][1] = 0; a.matrix[2][2] = 8; a.matrix[2][3] = 2;
	a.matrix[3][0] = -7; a.matrix[3][1] = 1; a.matrix[3][2] = -1; a.matrix[3][3] = 1;

	t_matrix expected = create_matrix(3);
	expected.matrix[0][0] = -6; expected.matrix[0][1] = 1; expected.matrix[0][2] = 6;
	expected.matrix[1][0] = -8; expected.matrix[1][1] = 8; expected.matrix[1][2] = 6;
	expected.matrix[2][0] = -7; expected.matrix[2][1] = -1; expected.matrix[2][2] = 1;

	t_matrix result = submatrix(a, 2, 1);
	assert(is_matrices_equal(result, expected) && "test_submatrix_4x4 failed");

	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_submatrix_4x4 passed\n");
}

// Test function for determinant of a 2x2 matrix
void test_determinant_2x2()
{
	t_matrix a = create_matrix(2);
	a.matrix[0][0] = 1; a.matrix[0][1] = 5;
	a.matrix[1][0] = -3; a.matrix[1][1] = 2;

	double result = determinant(a);
	assert(result == 17 && "test_determinant_2x2 failed");

	free_matrix(a);
	printf("test_determinant_2x2 passed\n");
}

// Test function for determinant of a 3x3 matrix
void test_determinant_3x3()
{
	t_matrix a = create_matrix(3);
	a.matrix[0][0] = 1; a.matrix[0][1] = 2; a.matrix[0][2] = 6;
	a.matrix[1][0] = -5; a.matrix[1][1] = 8; a.matrix[1][2] = -4;
	a.matrix[2][0] = 2; a.matrix[2][1] = 6; a.matrix[2][2] = 4;

	double result = determinant(a);
	assert(result == -196 && "test_determinant_3x3 failed");

	free_matrix(a);
	printf("test_determinant_3x3 passed\n");
}


// Function prints a matrix
void print_matrix(t_matrix m)
{
	for (int i = 0; i < m.size; i++)
	{
		for (int j = 0; j < m.size; j++)
		{
			printf("%f ", m.matrix[i][j]);
		}
		printf("\n");
	}
}

// Test function for inverse of a 4x4 matrix
void test_inverse_matrix()
{
	t_matrix a = create_matrix(4);
	a.matrix[0][0] = -5; a.matrix[0][1] = 2; a.matrix[0][2] = 6; a.matrix[0][3] = -8;
	a.matrix[1][0] = 1; a.matrix[1][1] = -5; a.matrix[1][2] = 1; a.matrix[1][3] = 8;
	a.matrix[2][0] = 7; a.matrix[2][1] = 7; a.matrix[2][2] = -6; a.matrix[2][3] = -7;
	a.matrix[3][0] = 1; a.matrix[3][1] = -3; a.matrix[3][2] = 7; a.matrix[3][3] = 4;

	t_matrix expected = create_matrix(4);
	expected.matrix[0][0] = 0.21805; expected.matrix[0][1] = 0.45113; expected.matrix[0][2] = 0.24060; expected.matrix[0][3] = -0.04511;
	expected.matrix[1][0] = -0.80827; expected.matrix[1][1] = -1.45677; expected.matrix[1][2] = -0.44361; expected.matrix[1][3] = 0.52068;
	expected.matrix[2][0] = -0.07895; expected.matrix[2][1] = -0.22368; expected.matrix[2][2] = -0.05263; expected.matrix[2][3] = 0.19737;
	expected.matrix[3][0] = -0.52256; expected.matrix[3][1] = -0.81391; expected.matrix[3][2] = -0.30075; expected.matrix[3][3] = 0.30639;

	t_matrix result = inverse_matrix(a);
	print_matrix(result);
	
	assert(is_matrices_equal(result, expected) && "test_inverse_matrix failed");

	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_inverse_matrix passed\n");
}

// Test function for inverse of another 4x4 matrix
void test_inverse_matrix_2()
{
	t_matrix a = create_matrix(4);
	a.matrix[0][0] = 8; a.matrix[0][1] = -5; a.matrix[0][2] = 9; a.matrix[0][3] = 2;
	a.matrix[1][0] = 7; a.matrix[1][1] = 5; a.matrix[1][2] = 6; a.matrix[1][3] = 1;
	a.matrix[2][0] = -6; a.matrix[2][1] = 0; a.matrix[2][2] = 9; a.matrix[2][3] = 6;
	a.matrix[3][0] = -3; a.matrix[3][1] = 0; a.matrix[3][2] = -9; a.matrix[3][3] = -4;

	t_matrix expected = create_matrix(4);
	expected.matrix[0][0] = -0.15385; expected.matrix[0][1] = -0.15385; expected.matrix[0][2] = -0.28205; expected.matrix[0][3] = -0.53846;
	expected.matrix[1][0] = -0.07692; expected.matrix[1][1] = 0.12308; expected.matrix[1][2] = 0.02564; expected.matrix[1][3] = 0.03077;
	expected.matrix[2][0] = 0.35897; expected.matrix[2][1] = 0.35897; expected.matrix[2][2] = 0.43590; expected.matrix[2][3] = 0.92308;
	expected.matrix[3][0] = -0.69231; expected.matrix[3][1] = -0.69231; expected.matrix[3][2] = -0.76923; expected.matrix[3][3] = -1.92308;

	t_matrix result = inverse_matrix(a);
	print_matrix(result);

	assert(is_matrices_equal(result, expected) && "test_inverse_matrix_2 failed");

	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_inverse_matrix_2 passed\n");
}

// Test function for inverse of a third 4x4 matrix
void test_inverse_matrix_3()
{
	t_matrix a = create_matrix(4);
	a.matrix[0][0] = 9; a.matrix[0][1] = 3; a.matrix[0][2] = 0; a.matrix[0][3] = 9;
	a.matrix[1][0] = -5; a.matrix[1][1] = -2; a.matrix[1][2] = -6; a.matrix[1][3] = -3;
	a.matrix[2][0] = -4; a.matrix[2][1] = 9; a.matrix[2][2] = 6; a.matrix[2][3] = 4;
	a.matrix[3][0] = -7; a.matrix[3][1] = 6; a.matrix[3][2] = 6; a.matrix[3][3] = 2;

	t_matrix expected = create_matrix(4);
	expected.matrix[0][0] = -0.04074; expected.matrix[0][1] = -0.07778; expected.matrix[0][2] = 0.14444; expected.matrix[0][3] = -0.22222;
	expected.matrix[1][0] = -0.07778; expected.matrix[1][1] = 0.03333; expected.matrix[1][2] = 0.36667; expected.matrix[1][3] = -0.33333;
	expected.matrix[2][0] = -0.02901; expected.matrix[2][1] = -0.14630; expected.matrix[2][2] = -0.10926; expected.matrix[2][3] = 0.12963;
	expected.matrix[3][0] = 0.17778; expected.matrix[3][1] = 0.06667; expected.matrix[3][2] = -0.26667; expected.matrix[3][3] = 0.33333;

	t_matrix result = inverse_matrix(a);
	print_matrix(result);

	assert(is_matrices_equal(result, expected) && "test_inverse_matrix_3 failed");

	free_matrix(a);
	free_matrix(expected);
	free_matrix(result);
	printf("test_inverse_matrix_3 passed\n");
}

// Test function for multiplying a product by its inverse
void test_multiply_product_by_inverse()
{
	t_matrix A = create_matrix(4);
	A.matrix[0][0] = 3; A.matrix[0][1] = -9; A.matrix[0][2] = 7; A.matrix[0][3] = 3;
	A.matrix[1][0] = 3; A.matrix[1][1] = -8; A.matrix[1][2] = 2; A.matrix[1][3] = -9;
	A.matrix[2][0] = -4; A.matrix[2][1] = 4; A.matrix[2][2] = 4; A.matrix[2][3] = 1;
	A.matrix[3][0] = -6; A.matrix[3][1] = 5; A.matrix[3][2] = -1; A.matrix[3][3] = 1;

	t_matrix B = create_matrix(4);
	B.matrix[0][0] = 8; B.matrix[0][1] = 2; B.matrix[0][2] = 2; B.matrix[0][3] = 2;
	B.matrix[1][0] = 3; B.matrix[1][1] = -1; B.matrix[1][2] = 7; B.matrix[1][3] = 0;
	B.matrix[2][0] = 7; B.matrix[2][1] = 0; B.matrix[2][2] = 5; B.matrix[2][3] = 4;
	B.matrix[3][0] = 6; B.matrix[3][1] = -2; B.matrix[3][2] = 0; B.matrix[3][3] = 5;

	t_matrix C = multiply_matrices(A, B);
	t_matrix B_inv = inverse_matrix(B);
	t_matrix result = multiply_matrices(C, B_inv);

	print_matrix(result);

	assert(is_matrices_equal(result, A) && "test_multiply_product_by_inverse failed");

	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(B_inv);
	free_matrix(result);
	printf("test_multiply_product_by_inverse passed\n");
}

int main()
{
	test_submatrix_3x3();
	test_submatrix_4x4();
	test_determinant_2x2();
	test_determinant_3x3();
	test_inverse_matrix();
	test_inverse_matrix_2();
	test_inverse_matrix_3();
	test_multiply_product_by_inverse();
	printf("All tests passed!\n");
	return 0;
}