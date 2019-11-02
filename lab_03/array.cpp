#include <cstdlib>

#include "array.hpp"

void array_read(std::istream &stream, int * const arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        stream >> arr[i];
}

void array_randomize(int * const arr, size_t n, int min, int max)
{
    for (size_t i = 0; i < n; i++)
        arr[i] = rand() % (max - min + 1) + min;
}

void array_write(std::ostream &stream, const int * const arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        stream << arr[i] << ' ';
}

void array_sort_insert(int * const arr, size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            arr[j] = tmp;
            j--;
        }
    }
}

void array_merge(int * const arr, size_t first, size_t last)
{
    size_t len = last - first + 1;
    size_t middle = (first + last) / 2;
    size_t start_1 = first;
    size_t start_2 = middle + 1;

    int *arr_tmp = new int[len];

    for (size_t i = 0; i < len; i++)
        if ((start_1 <= middle) && ((start_2 > last) ||
            (arr[start_1] < arr[start_2])))
        {
            arr_tmp[i] = arr[start_1];
            start_1++;
        }
        else
        {
            arr_tmp[i] = arr[start_2];
            start_2++;
        }

    for (size_t i = first; i <= last; i++)
        arr[i] = arr_tmp[i - first];
    delete [] arr_tmp;
}

void array_sort_merge(int * const arr, size_t first, size_t last)
{
    if (first < last)
    {
        size_t middle = (first + last) / 2;
        array_sort_merge(arr, first, middle);
        array_sort_merge(arr, middle + 1, last);
        array_merge(arr, first, last);
    }
}

void array_sort_quick(int * const arr, size_t first, size_t last)
{
    size_t l_hold = first;
    size_t r_hold = last;
    int pivot = arr[(first + last) / 2];

    while (first <= last)
    {
        while (arr[first] < pivot)
            first++;
        while (arr[last] > pivot)
            last--;
        if (first <= last)
        {
            int tmp = arr[last];
            arr[last] = arr[first];
            arr[first] = tmp;
            first++;
            last--;
        }
    }

    if (l_hold < last)
        array_sort_quick(arr, l_hold, last);
    if (r_hold > first)
        array_sort_quick(arr, first, r_hold);
}