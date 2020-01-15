#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "array.hpp"

int main(int argc,char **argv)
{
    srand(time(NULL));

    if (argc == 2 && std::string(argv[1]) == "-memcheck")
    {
        size_t n = 10;
        size_t bytes_to_copy = n * sizeof(int);

        int *arr = new int[n];
        array_randomize(arr, n, -1000, 1000);
        int *to_sort = new int[n];

        memcpy(to_sort, arr, bytes_to_copy);
        array_sort_insert(to_sort, n);

        memcpy(to_sort, arr, bytes_to_copy);
        array_sort_merge(to_sort, 0, n - 1);

        memcpy(to_sort, arr, bytes_to_copy);
        array_sort_quick(to_sort, 0, n - 1);

        delete [] arr;
        delete [] to_sort;

        return 0;
    }

    size_t n = 0;
    std::cout << "Enter size of array: ";
    std::cin >> n;

    size_t bytes_to_copy = n * sizeof(int);

    int *arr = new int[n];
    if (argc == 2 && std::string(argv[1]) == "-rand")
        array_randomize(arr, n, -1000, 1000);
    else
    {
        std::cout << "Enter array: ";
        array_read(std::cin, arr, n);
    }
    int *to_sort = new int[n];

    std::cout << std::endl << "Source: ";
    array_write(std::cout, arr, n);

    memcpy(to_sort, arr, bytes_to_copy);
    array_sort_insert(to_sort, n);
    std::cout << std::endl << "Insert: ";
    array_write(std::cout, to_sort, n);

    memcpy(to_sort, arr, bytes_to_copy);
    array_sort_merge(to_sort, 0, n - 1);
    std::cout << std::endl << "Merge: ";
    array_write(std::cout, to_sort, n);

    memcpy(to_sort, arr, bytes_to_copy);
    array_sort_quick(to_sort, 0, n - 1);
    std::cout << std::endl << "Quick: ";
    array_write(std::cout, to_sort, n);

    delete [] arr;
    delete [] to_sort;

    return 0;
}