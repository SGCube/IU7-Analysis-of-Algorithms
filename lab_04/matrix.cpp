#include "matrix.hpp"
#include <iostream>
#include <cstdlib>

Matrix::Matrix(unsigned rows, unsigned cols)
{
    _rows = rows;
    _cols = cols;

    ptr = new int * [_rows];
    for (unsigned i = 0; i < _rows; i++)
    {
        ptr[i] = new int[_cols];
        for (unsigned j = 0; j < _cols; j++)
            ptr[i][j] = 0;
    }
}

Matrix::Matrix(std::istream& stream)
{
    stream >> _rows;
    stream >> _cols;
    ptr = new int * [_rows];

    for (unsigned i = 0; i < _rows; i++)
    {
        ptr[i] = new int[_cols];
        for (unsigned j = 0; j < _cols; j++)
            stream >> ptr[i][j];
    }
}

Matrix::~Matrix()
{
    for (unsigned i = 0; i < _rows; i++)
        delete [] ptr[i];
    delete [] ptr;
}

void Matrix::read(std::istream& stream)
{
    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            stream >> ptr[i][j];
}

void Matrix::write(std::ostream& stream)
{
    for (unsigned i = 0; i < _rows; i++)
    {
        for (unsigned j = 0; j < _cols; j++)
            stream << ptr[i][j] << ' ';
        stream  << std::endl;
    }
}

void Matrix::randomize(int min, int max)
{
    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            ptr[i][j] = rand() % (max - min + 1) + min;
}

bool Matrix::operator==(const Matrix &other)
{
    if (self._rows != other._rows || self._cols != other._cols)
        return false;

    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            if (self.ptr[i][j] != other.ptr[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix &other)
{
    return !(self == other);
}

void set_rows(unsigned rows)
{
    _rows = rows;
}

unsigned get_rows()
{
    return _rows;
}

void set_cols(unsigned cols)
{
    _cols = cols;
}

unsigned get_cols()
{
    return _cols;
}

int** matr()
{
    return ptr;
}
