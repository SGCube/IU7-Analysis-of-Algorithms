#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

class Matrix
{
private:
    int **ptr;
    size_t _rows;
    size_t _columns;
 
public:
    Matrix(size_t rows, size_t columns);
    ~Matrix();
 
    size_t get_rows() const;
    size_t get_columns() const;
    int **get_ptr() const;
    int *operator[](size_t index);
    void randomize(int min, int max);
    Matrix operator*(const Matrix &right);
    const Matrix &operator=(const Matrix &right);
    bool operator==(const Matrix &right);
};

std::istream& operator>>(std::istream& stream, Matrix& matrix);

std::ostream& operator<<(std::ostream& stream, Matrix& matrix);

#endif
