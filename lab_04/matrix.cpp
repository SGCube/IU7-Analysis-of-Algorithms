#include "matrix.hpp"
#include <iostream>
#include <cstdlib>

Matrix::Matrix(unsigned rows, unsigned cols)
{
    _rows = rows;
    _cols = cols;

    ptr = new Array(_cols)[_rows];
}

Matrix::Matrix(std::istream& stream)
{
    stream >> _rows;
    stream >> _cols;

    ptr = new Array(_cols)[_rows];

    for (unsigned i = 0; i < _rows; i++)
        ptr[i].read(stream);
}

Matrix::Matrix(const Matrix &other)
{
    _rows = other._rows;
    _cols = other._cols;

    ptr = new Array(_cols)[_rows];
    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            ptr[i][j] = other.ptr[i][j];
}

Matrix::~Matrix()
{
    delete [] ptr;
}

void Matrix::read(std::istream& stream)
{
    for (unsigned i = 0; i < _rows; i++)
        ptr[i].read(stream);
}

void Matrix::write(std::ostream& stream)
{
    for (unsigned i = 0; i < _rows; i++)
        ptr[i].write(stream);
}

void Matrix::randomize(int min, int max)
{
    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            ptr[i][j] = rand() % (max - min + 1) + min;
}

Matrix& Matrix::operator=(Matrix &other)
{
    Matrix tmp(other._rows, other._cols);
    for (unsigned i = 0; i < tmp._rows; i++)
        for (unsigned j = 0; j < tmp._cols; j++)
            tmp.ptr[i][j] = other.ptr[i][j];
    
    return tmp;
}

bool Matrix::operator==(const Matrix &other)
{
    if (this._rows != other._rows || this._cols != other._cols)
        return false;

    for (unsigned i = 0; i < _rows; i++)
        for (unsigned j = 0; j < _cols; j++)
            if (this.ptr[i][j] != other.ptr[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix &other)
{
    return !(this == other);
}

unsigned Matrix::get_rows()
{
    return _rows;
}

unsigned Matrix::get_cols()
{
    return _cols;
}

Array& Matrix::operator[](unsigned i)
{
    return ptr[i];
}
