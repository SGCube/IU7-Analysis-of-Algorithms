#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

namespace Matrix
{
    int **init(unsigned rows, unsigned cols);

    void destroy(int **matr, unsigned rows);

    void randomize(int **matr, unsigned rows, unsigned cols,
        int min, int max);
    
    int **randinit(unsigned rows, unsigned cols, int min, int max);

    int **read(std::istream& stream, int **matr, unsigned &rows,
        unsigned &cols);

    int **read_wsize(std::istream& stream, unsigned &rows, unsigned &cols);

    void write(std::ostream& stream, int **matr, unsigned rows,
        unsigned cols);
    
    bool equal(int **matr1, unsigned rows1, unsigned cols1,
        int **matr2, unsigned rows2, unsigned cols2);
};

#endif
