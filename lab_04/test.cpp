#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "mamult.hpp"

int handle_result(Matrix &C, Matrix &CC)
{
    if (C == CC)
    {
        std::cout << "PASSED" << std::endl;
        return 0;
    }

    std::cout << "FAILED" << std::endl;
    std::cout << "Expected:" << std::endl;
    C.write(std::cout);
    std::cout << "Got:" << std::endl;
    CC.write(std::cout);
    return 1;
}

int main(void)
{
    int error_count = 0;
    for (int i = 1; i <= 6; i++)
    {
        char fname_1[30], fname_2[30], fname_res[30];
        sprintf(fname_1, "tests/in_%d_0.txt", i);
        sprintf(fname_2, "tests/in_%d_1.txt", i);
        sprintf(fname_res, "tests/out_%d.txt", i);

        std::ifstream fin_1(fname_1);
        std::ifstream fin_2(fname_2);
        std::ifstream fin_res(fname_res);

        std::cout << "TEST " << i << ": " << std::endl;

        Matrix A(fin_1), B(fin_2), C(fin_res);

        Matrix CC = multiply_vinograd_thread(A, B, 8);
        error_count += handle_result(C, CC);

        fin_1.close();
        fin_2.close();
        fin_res.close();
    }
    return error_count;
}