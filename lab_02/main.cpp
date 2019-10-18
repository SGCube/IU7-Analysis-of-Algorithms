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

        int **matrix_a = Matrix::randinit(m, n, -10, 10);
        int **matrix_b = Matrix::randinit(n, q, -10, 10);
        int **matrix_c = Matrix::init(m, q);

        multiply_classic(matrix_a, matrix_b, matrix_c, m, n, q);
        multiply_vinograd(matrix_a, matrix_b, matrix_c, m, n, q);
        multiply_vinograd_opt(matrix_a, matrix_b, matrix_c, m, n, q);

        Matrix::destroy(matrix_a, m);
        Matrix::destroy(matrix_b, n);
        Matrix::destroy(matrix_a, q);
        
        return 0;
    }

    unsigned m, n, q;
    std::cout << "Enter 3 size of matrices (M, N, Q): ";
    std::cin >> m >> n >> q;

    int **matrix_a = Matrix::randinit(m, n, -10, 10);
    int **matrix_b = Matrix::randinit(n, q, -10, 10);

    std::cout << std::endl;
    Matrix::write(std::cout, matrix_a, m, n);
    std::cout << std::endl;
    Matrix::write(std::cout, matrix_b, n, q);
    std::cout << std::endl;

    int **matrix_c = Matrix::init(m, q);

    multiply_classic(matrix_a, matrix_b, matrix_c, m, n, q);
    Matrix::write(std::cout, matrix_c, m, q);
    std::cout << std::endl;

    multiply_vinograd(matrix_a, matrix_b, matrix_c, m, n, q);
    Matrix::write(std::cout, matrix_c, m, q);
    std::cout << std::endl;

    multiply_vinograd_opt(matrix_a, matrix_b, matrix_c, m, n, q);
    Matrix::write(std::cout, matrix_c, m, q);
    std::cout << std::endl;

    Matrix::destroy(matrix_a, m);
    Matrix::destroy(matrix_b, n);
    Matrix::destroy(matrix_a, q);

    return 0;
}