#include <iostream>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"

int main(void)
{
    srand(time(NULL));

    size_t m, n, q;
    std::cin >> m >> n >> q;

    Matrix matrix_a(m, n), matrix_b(n, q);
    matrix_a.randomize(-10, 10);
    matrix_b.randomize(-10, 10);
    Matrix matrix_c = matrix_a * matrix_b;

    std::cout << matrix_a << std::endl;
    std::cout << matrix_b << std::endl;
    std::cout << matrix_c << std::endl;

    return 0;
}