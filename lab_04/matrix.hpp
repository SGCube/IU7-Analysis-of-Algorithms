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

    Array(const Array& other)
    {
        _size = other._size;
        ptr = new int[_size];
        for (unsigned i = 0; i < _size; i++)
            ptr[i] = other.ptr[i];
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
    Matrix(const Matrix &other);
    ~Matrix();

    void read(std::istream& stream);
    void write(std::ostream& stream);

    void randomize(int min, int max);

    Matrix& operator=(Matrix other);

    bool operator==(const Matrix &other);
    bool operator!=(const Matrix &other);

    unsigned get_rows();
    unsigned get_cols();
    Array& operator[] (unsigned i);

private:
    Array *ptr;
    unsigned _rows;
    unsigned _cols;
};

#endif
