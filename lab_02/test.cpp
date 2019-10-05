#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "vinograd.hpp"

void handle_result(Matrix &expected, Matrix &got)
{
    if (expected == got)
        std::cout << "PASSED" << std::endl;
    else
    {
        std::cout << "FAILED" << std::endl;
        std::cout << "Expected:" << std::endl << expected << std::endl;
        std::cout << "Got:" << std::endl << got << std::endl;
    }
}

int main(void)
{
    for (int i = 1; i <= 6; i++)
    {
        char fname_1[20], fname_2[20], fname_res[20];
        sprintf(fname_1, "in_%d_0.txt", i);
        sprintf(fname_2, "in_%d_1.txt", i);
        sprintf(fname_res, "out_%d.txt", i);

        std::ifstream fin_1(fname_1);
        std::ifstream fin_2(fname_2);
        std::ifstream fin_res(fname_res);

        size_t rows_a = 0, rows_b = 0, rows_c = 0;
        size_t cols_a = 0, cols_b = 0, cols_c = 0;

        fin_1 >> rows_a;
        fin_1 >> cols_a;
        fin_2 >> rows_b;
        fin_2 >> cols_b;
        fin_res >> rows_c;
        fin_res >> cols_c;

        Matrix A(rows_a, cols_a), B(rows_b, cols_b), C(rows_c, cols_c);
        fin_1 >> A;
        fin_2 >> B;
        fin_res >> C;

        std::cout << "TEST " << i << ": " << std::endl;
        std::cout << A << B;

        Matrix test_0 = A * B;
        Matrix test_1 = multiply_vinograd(A, B);
        Matrix test_2 = multiply_vinograd_opt(A, B);

        std::cout << "1) Classic: ";
        handle_result(C, test_0);
        std::cout << "2) Vinograd: ";
        handle_result(C, test_1);
        std::cout << "3) Vinograd (optimized): ";
        handle_result(C, test_2);

        fin_1.close();
        fin_2.close();
        fin_res.close();
    }
    return 0;
}