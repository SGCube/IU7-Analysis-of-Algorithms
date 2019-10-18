#include "gtest/gtest.h"

#include "matrix.hpp"
#include "mamult.hpp"

TEST(Size_1x1, Classic)
{
    int **A = {{5}};
    int **B = {{-8}};
    int **C = {{-40}};
    int **CC = Matrix::init(1, 1);

    multiply_classic(A, B, CC, 1, 1, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

TEST(Size_1x1, Vinograd)
{
    int **A = {{5}};
    int **B = {{-8}};
    int **C = {{-40}};
    int **CC = Matrix::init(1, 1);

    multiply_vinograd(A, B, CC, 1, 1, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

TEST(Size_1x1, Optimized)
{
    int **A = {{5}};
    int **B = {{-8}};
    int **C = {{-40}};
    int **CC = Matrix::init(1, 1);

    multiply_vinograd_opt(A, B, CC, 1, 1, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

TEST(Size_1x3_3x1, Classic)
{
    int **A = {{2, 1, 1}};
    int **B = {{1}, {-1}, {5}};
    int **C = {{6}};
    int **CC = Matrix::init(1, 1);

    multiply_classic(A, B, CC, 1, 3, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

TEST(Size_1x3_3x1, Vinograd)
{
    int **A = {{2, 1, 1}};
    int **B = {{1}, {-1}, {5}};
    int **C = {{6}};
    int **CC = Matrix::init(1, 1);

    multiply_vinograd(A, B, CC, 1, 3, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

TEST(Size_1x3_3x1, Optimized)
{
    int **A = {{2, 1, 1}};
    int **B = {{1}, {-1}, {5}};
    int **C = {{6}};
    int **CC = Matrix::init(1, 1);

    multiply_vinograd_opt(A, B, CC, 1, 1, 1);
    ASSERT_TRUE(Matrix::equal(C, 1, 1, CC, 1, 1));

    delete [] CC;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}