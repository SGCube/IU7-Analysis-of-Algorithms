#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

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

#define DESC -1
#define RAND 0
#define ASC 1

void time_measure(std::ofstream &file, unsigned start_size, unsigned end_size,
                    unsigned step, int array_type)
{
    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 1000;

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long results[3] = { 0, 0, 0 };
        for (unsigned k = 0; k < test_repeats; k++)
        {
            unsigned bytes_to_copy = size * sizeof(int);

            int *arr = new int[size];
            int *to_sort = new int[size];

            switch(array_type)
            {
            case DESC:
                array_sorted(arr, size, size - 1, -1);
                break;
            case ASC:
                array_sorted(arr, size, 1, 1);
                break;
            default:
                array_randomize(arr, size, 0, size - 1);
            }
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
            array_sorted(to_sort, size, 1, 1);
            start_time = rdtsc();
            array_sort_quick_left(to_sort, 0, size - 1);
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

    std::ofstream csv_rand("report/RandTime.csv");
    if (!csv_rand.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_rand << "Size;Insert;Merge;Quick\n";
    time_measure(csv_rand, 100, 1000, 100, RAND);
    csv_rand.close();

    std::ofstream csv_desc("report/DescTime.csv");
    if (!csv_desc.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_desc << "Size;Insert;Merge;Quick\n";
    time_measure(csv_desc, 100, 1000, 100, DESC);
    csv_desc.close();

    std::ofstream csv_asc("report/AscTime.csv");
    if (!csv_asc.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_asc << "Size;Insert;Merge;Quick\n";
    time_measure(csv_asc, 100, 1000, 100, ASC);
    csv_asc.close();

    std::cout << "OK!" << std::endl;

    return 0;
}