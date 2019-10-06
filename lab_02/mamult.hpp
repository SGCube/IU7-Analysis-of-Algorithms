#ifndef MAMULT_HPP
#define MAMULT_HPP

#include "matrix.hpp"

void multiply_classic(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q);

void multiply_vinograd(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q);

void multiply_vinograd_opt(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q);

#endif
