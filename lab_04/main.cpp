#include <iostream>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"
#include "mamult.hpp"

int main(int argc, char **argv)
{
    srand(time(NULL));

    if (argc == 2 && std::string(argv[1]) == "-memcheck")
    {
        unsigned m = 10, n = 20, q = 30;

        Matrix A(m, n), B(n, q), C(m, q);
        A.randomize(-10, 10);
        B.randomize(-10, 10);

        multiply_vinograd_opt(matrix_a, matrix_b, matrix_c, m, n, q);

        return 0;
    }

    unsigned m, n, q;
    std::cout << "Enter 3 size of matrices (M, N, Q): ";
    std::cin >> m >> n >> q;

    Matrix A(m, n), B(n, q), C(m, q);
    A.randomize(-10, 10);
    B.randomize(-10, 10);

    std::cout << std::endl;
    A.write(std::cout);
    std::cout << std::endl;
    B.write(std::cout);
    std::cout << std::endl;

    Matrix C = multiply_vinograd_opt(matrix_a, matrix_b, matrix_c, m, n, q);
    C.write(std::cout);
    std::cout << std::endl;

    return 0;
}