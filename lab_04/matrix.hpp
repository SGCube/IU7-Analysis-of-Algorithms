#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Array
{
public:
    Array(unsigned size)
    {
        _size = size;
        ptr = new int[_size];
        for (unsigned i = 0; i < _size; i++)
            ptr[i] = 0;
    }

    ~Array()
    {
        delete [] ptr;
    }

    void read(std::istream& stream)
    {
        for (unsigned i = 0; i < _size; i++)
            stream >> ptr[i];
    }

    void write(std::ostream& stream)
    {
        for (unsigned i = 0; i < _size; i++)
            stream << ptr[i] << ' ';
    }
 
    int& operator[](unsigned i)
    {
        return ptr[i];
    }

    friend Matrix;

private:
    int *ptr;
    unsigned _size;
};

class Matrix
{
public:
    Matrix(unsigned rows, unsigned cols);
    Matrix(std::istream& stream);
    ~Matrix();

    void read(std::istream& stream);
    void write(std::ostream& stream);

    void randomize(int min, int max);

    bool operator==(const Matrix &other);
    bool operator!=(const Matrix &other);

    void set_rows(unsigned rows);
    unsigned get_rows();

    void set_cols(unsigned cols);
    unsigned get_cols();

    Array& operator[] (unsigned i)
    {
        return arrays[i];
    }

    int** matr();

private:
    int **ptr;
    unsigned _rows;
    unsigned _cols;

    Array *arrays;
};

#endif
