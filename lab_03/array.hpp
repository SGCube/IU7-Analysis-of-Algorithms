#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

void array_read(std::istream &stream, int * const arr, size_t n);

void array_randomize(int * const arr, size_t n, int min, int max);

void array_sorted(int * const arr, size_t n, int start, int step);

void array_write(std::ostream &stream, const int * const arr, size_t n);

void array_sort_insert(int * const arr, size_t n);

void array_sort_merge(int * const arr, size_t first, size_t last);

void array_sort_quick(int * const arr, size_t first, size_t last);

void array_sort_quick_left(int * const arr, size_t first, size_t last);

#endif