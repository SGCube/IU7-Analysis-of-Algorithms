#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"
#include "mamult.hpp"

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

void time_measure(std::ofstream &file, unsigned start_size, unsigned end_size, unsigned step)
{
    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 100;
    file << "Size;Thread\n";

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long result = 0;
        for (unsigned k = 0; k < test_repeats; k++)
        {
            int **matrix_a = Matrix::randinit(size, size, -10, 10);
            int **matrix_b = Matrix::randinit(size, size, -10, 10);
            int **matrix_c = Matrix::init(size, size);

            start_time = rdtsc();
            multiply_vinograd_opt(matrix_a, matrix_b, matrix_c, size, size, size);
            end_time = rdtsc();
            result += end_time - start_time;
        }
        file << size;
        result /= test_repeats;
        file << ";" << result << std::endl;
    }
}

int main(void)
{
    srand(time(NULL));

    std::ofstream csv_even("report/EvenTime.csv");
    if (!csv_even.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    time_measure(csv_even, 100, 1000, 100);
    csv_even.close();

    std::ofstream csv_odd("report/ThreadTime.csv");
    if (!csv_odd.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    time_measure(csv_odd, 101, 1010, 100);
    csv_odd.close();

    return 0;
}
