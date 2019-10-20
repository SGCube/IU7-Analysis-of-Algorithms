#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "array.hpp"
#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc() {
	return __rdtsc();
}
#else
uint64_t rdtsc() 
{
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
#endif

void time_measure(std::ofstream &file, unsigned start_size, unsigned end_size,
                    unsigned step)
{
    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 100;

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long results[3] = { 0, 0, 0 };
        for (unsigned k = 0; k < test_repeats; k++)
        {
            unsigned bytes_to_copy = size * sizeof(int);

            int *arr = new int[size];
            array_randomize(arr, size, -1000, 1000);
            int *to_sort = new int[size];

            memcpy(to_sort, arr, bytes_to_copy);
            start_time = rdtsc();
            array_sort_insert(to_sort, size);
            end_time = rdtsc();
            results[0] += end_time - start_time;

            memcpy(to_sort, arr, bytes_to_copy);
            start_time = rdtsc();
            array_sort_merge(to_sort, 0, size - 1);
            end_time = rdtsc();
            results[1] += end_time - start_time;

            memcpy(to_sort, arr, bytes_to_copy);
            start_time = rdtsc();
            array_sort_quick(to_sort, 0, size - 1);
            end_time = rdtsc();
            results[2] += end_time - start_time;

            delete [] arr;
            delete [] to_sort;
        }
        file << size;
        for (unsigned k = 0; k < 3; k++)
        {
            results[k] /= test_repeats;
            file << ";" << results[k];
        }
        file << "\n";
    }
}

int main(void)
{
    srand(time(NULL));

    std::ofstream csv_sort("report\\SortTime.csv");
    if (!csv_sort.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_sort << "Size;Insert;Merge;Quick\n";
    time_measure(csv_sort, 100, 1000, 50);
    csv_sort.close();

    return 0;
}