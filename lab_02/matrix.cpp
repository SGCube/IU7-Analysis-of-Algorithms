#include "matrix.hpp"
#include <iostream>
#include <cstdlib>

Matrix::Matrix(size_t rows, size_t columns)
{
    _rows = rows;
    _columns = columns;
    ptr = new int*[_rows];

    for (size_t i = 0; i < _rows; i++)
    {
        ptr[i] = new int[_columns];
        for (size_t j = 0; j < _columns; j++)
            ptr[i][j] = 0;
    }
}
 
Matrix::~Matrix()
{
   delete [] ptr;
}
 
size_t Matrix::get_rows() const
{
    return _rows;
}

size_t Matrix::get_columns() const
{
    return _columns;
}
 
int **Matrix::get_ptr() const
{
    return ptr;
}
 
int *Matrix::operator[](size_t index)
{
    if (index < 0 || index >= _rows)
    {
        std::cerr << "\n Ошибка индекса: " << index << std::endl;
        exit(1);
    }
    return ptr[index];
}
 
void Matrix::randomize(int min, int max)
{
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < _columns; j++)
            ptr[i][j] = rand() % (max - min + 1) + min;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix)
{
   for (size_t i = 0; i < matrix.get_rows(); i++)
        for (size_t j = 0; j < matrix.get_columns(); j++)
            stream >> matrix[i][j];

    return stream;
}

std::ostream& operator<<(std::ostream& stream, Matrix& matrix)
{
   for (size_t i = 0; i < matrix.get_rows(); i++)
    {
        for (size_t j = 0; j < matrix.get_columns(); j++)
            stream << matrix[i][j] << ' ';
        stream  << std::endl;
    }

    return stream;
}
 
Matrix Matrix::operator* (const Matrix &right)
{
    if (_columns != right._rows)
    {
        std::cout << "Matrices sizes are not matched!\n";
        exit(1);
    }
 
    Matrix result(_rows, right._columns);
    for (size_t i = 0; i < _rows; i++)
        for (size_t j = 0; j < right._columns; j++)
            for (size_t k = 0; k < _columns; k++)
                result.ptr[i][j] += ptr[i][k] * right.ptr[k][j];
    return result;
}

bool Matrix::operator== (const Matrix &right)
{
    if (&right != this)
    {
        if (_rows != right._rows || _columns != right._columns)
            return false;
 
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _columns; j++)
                if (ptr[i][j] != right.ptr[i][j])
                    return false;
    }
 
    return true;
}
 
const Matrix &Matrix::operator= (const Matrix &right)
{
    if (&right != this)
    {
        if (_rows != right._rows || _columns != right._columns)
        {
            delete [] ptr;
            _rows = right._rows;
            _columns = right._columns;

            ptr = new int*[_rows];
            for (int i = 0; i < _rows; i++)
                ptr[i] = new int[right._columns];
        }
 
        for (int i = 0; i < _rows; i++)
            for (int j = 0; j < _columns; j++)
                ptr[i][j] = right.ptr[i][j];
    }
 
    return *this;
}