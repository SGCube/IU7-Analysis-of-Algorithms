#ifndef MAMULT_HPP
#define MAMULT_HPP

#include "matrix.hpp"

Matrix& multiply_vinograd_opt(const Matrix &A, const Matrix &B);

Matrix& multiply_vinograd_nothread(const Matrix &A, const Matrix &B);

#endif
