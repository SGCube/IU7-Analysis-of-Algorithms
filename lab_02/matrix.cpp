#include "matrix.hpp"
#include <iostream>
#include <cstdlib>

namespace Matrix
{
    int **init(unsigned rows, unsigned cols)
    {
        int **matr = new int * [rows];
        for (unsigned i = 0; i < rows; i++)
        {
            matr[i] = new int[cols];
            for (unsigned j = 0; j < cols; j++)
                matr[i][j] = 0;
        }
        return matr;
    }

    void destroy(int **matr, unsigned rows)
    {
        for (unsigned i = 0; i < rows; i++)
            delete [] matr[i];
        delete [] matr;
    }

    void randomize(int **matr, unsigned rows, unsigned cols, int min, int max)
    {
        for (unsigned i = 0; i < rows; i++)
            for (unsigned j = 0; j < cols; j++)
                matr[i][j] = rand() % (max - min + 1) + min;
    }

    int **randinit(unsigned rows, unsigned cols, int min, int max)
    {
        int **matr = new int * [rows];
        for (unsigned i = 0; i < rows; i++)
        {
            matr[i] = new int[cols];
            for (unsigned j = 0; j < cols; j++)
                matr[i][j] = rand() % (max - min + 1) + min;
        }
        return matr;
    }

    int **read_wsize(std::istream& stream, unsigned &rows, unsigned &cols)
    {
        stream >> rows;
        stream >> cols;
        int **matr = Matrix::init(rows, cols);

        for (unsigned i = 0; i < rows; i++)
            for (unsigned j = 0; j < cols; j++)
                stream >> matr[i][j];

        return matr;
    }

    void read(std::istream& stream, int **matr, unsigned rows, unsigned cols)
    {
        for (unsigned i = 0; i < rows; i++)
            for (unsigned j = 0; j < cols; j++)
                stream >> matr[i][j];
    }

    void write(std::ostream& stream, int **matr, unsigned rows, unsigned cols)
    {
        for (unsigned i = 0; i < rows; i++)
        {
            for (unsigned j = 0; j < cols; j++)
                stream << matr[i][j] << ' ';
            stream  << std::endl;
        }
    }
    
    bool equal(int **matr1, unsigned rows1, unsigned cols1,
        int **matr2, unsigned rows2, unsigned cols2)
    {
        if (rows1 != rows2 || cols1 != cols2)
            return false;

        for (unsigned i = 0; i < rows1; i++)
            for (unsigned j = 0; j < cols1; j++)
                if (matr1[i][j] != matr2[i][j])
                    return false;
        return true;
    }
};