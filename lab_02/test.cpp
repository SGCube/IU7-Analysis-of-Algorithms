#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "mamult.hpp"

int handle_result(int **matr1, unsigned rows1, unsigned cols1,
        int **matr2, unsigned rows2, unsigned cols2)
{
    if (Matrix::equal(matr1, rows1, cols1, matr2, rows2, cols2))
    {
        std::cout << "PASSED" << std::endl;
        return 0;
    }

    std::cout << "FAILED" << std::endl;
    std::cout << "Expected:" << std::endl;
    Matrix::write(std::cout, matr1, rows1, cols1);
    std::cout << "Got:" << std::endl;
    Matrix::write(std::cout, matr2, rows2, cols2);
    return 1;
}

int main(void)
{
    int error_count = 0;
    for (int i = 1; i <= 6; i++)
    {
        char fname_1[20], fname_2[20], fname_res[20];
        sprintf(fname_1, "in_%d_0.txt", i);
        sprintf(fname_2, "in_%d_1.txt", i);
        sprintf(fname_res, "out_%d.txt", i);

        std::ifstream fin_1(fname_1);
        std::ifstream fin_2(fname_2);
        std::ifstream fin_res(fname_res);

        unsigned rows_a = 0, rows_b = 0, rows_c = 0;
        unsigned cols_a = 0, cols_b = 0, cols_c = 0;

        int **A = Matrix::read_wsize(fin_1, rows_a, cols_a);
        int **B = Matrix::read_wsize(fin_2, rows_b, cols_b);
        int **C = Matrix::read_wsize(fin_res, rows_c, cols_c);
        int **CC = Matrix::init(rows_a, cols_b);

        std::cout << "TEST " << i << ": " << std::endl;

        multiply_classic(A, B, CC, rows_a, cols_a, cols_b);
        std::cout << "1) Classic: ";
        error_count += handle_result(C, rows_c, cols_c, CC, rows_a, cols_b);

        multiply_vinograd(A, B, CC, rows_a, cols_a, cols_b);
        std::cout << "2) Vinograd: ";
        error_count += handle_result(C, rows_c, cols_c, CC, rows_a, cols_b);

        multiply_vinograd_opt(A, B, CC, rows_a, cols_a, cols_b);
        std::cout << "3) V. Optimized: ";
        error_count += handle_result(C, rows_c, cols_c, CC, rows_a, cols_b);

        fin_1.close();
        fin_2.close();
        fin_res.close();
    }
    return error_count;
}