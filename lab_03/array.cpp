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
    int *arr_tmp = new int[last - first + 1];
    size_t middle = (first + last) / 2;
    size_t start = first;
    size_t final = middle + 1;

    for (size_t i = first; i <= last; i++)
        if ((start <= middle) && ((final > last) || (arr[start] < arr[final])))
        {
            arr_tmp[i] = arr[start];
            start++;
        }
        else
        {
            arr_tmp[i] = arr[final];
            final++;
        }

    for (size_t i = first; i <= last; i++)
        arr[i] = arr_tmp[i];
    delete [] arr_tmp;
}

void array_sort_merge(int * const arr, size_t first, size_t last)
{
    if (first < last)
    {
        std::cout << std::endl;
        array_write(std::cout, &arr[first], last - first + 1);
        size_t middle = (first + last) / 2;
        array_sort_merge(arr, first, middle);
        array_sort_merge(arr, middle + 1, last);
        array_merge(arr, first, last);
        std::cout << std::endl << "!:\t";
        array_write(std::cout, &arr[first], last - first + 1);
    }
}

void array_sort_quick(int * const arr, size_t first, size_t last)
{
    size_t l_hold = first;
    size_t r_hold = last;
    int pivot = arr[first];

    while (first < last)
    {
        while ((arr[last] >= pivot) && (first < last))
            last--;
        if (first != last)
        {
            arr[first] = arr[last];
            first++;
        }
        while ((arr[first] <= pivot) && (first < last))
            first++;
        if (first != last)
        {
            arr[last] = arr[first];
            last--;
        }
    }

    size_t middle = first;
    arr[middle] = pivot;
    if (l_hold < middle)
        array_sort_quick(arr, l_hold, middle - 1);
    if (r_hold > middle)
        array_sort_quick(arr, middle + 1, r_hold);
}