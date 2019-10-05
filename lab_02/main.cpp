#include <iostream>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"
#include "vinograd.hpp"

int main(void)
{
    srand(time(NULL));

    size_t m, n, q;
    std::cin >> m >> n >> q;

    Matrix matrix_a(m, n), matrix_b(n, q);
    matrix_a.randomize(-10, 10);
    matrix_b.randomize(-10, 10);

    Matrix matrix_c = matrix_a * matrix_b;
    Matrix matrix_c1 = multiply_vinograd(matrix_a, matrix_b);
    Matrix matrix_c2 = multiply_vinograd_opt(matrix_a, matrix_b);

    std::cout << std::endl << matrix_a << std::endl;
    std::cout << matrix_b << std::endl << std::endl;

    std::cout << matrix_c << std::endl;
    std::cout << matrix_c1 << std::endl;
    std::cout << matrix_c2 << std::endl;

    return 0;
}