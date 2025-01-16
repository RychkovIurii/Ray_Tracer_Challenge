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

int main()
{
    test_submatrix_3x3();
    test_submatrix_4x4();
    test_determinant_2x2();
    test_determinant_3x3();
    printf("All tests passed!\n");
    return 0;
}