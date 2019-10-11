#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "leven.hpp"
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

std::string random_string(unsigned size)
{
    std::string s;
    for (unsigned i = 0; i < size; i++)
        s.push_back(rand() % ('z' - 'a' + 1) + 'a');
    return s;
}

void time_measure(std::ofstream &file, unsigned start_size, unsigned end_size,
                    unsigned step, unsigned (*f1)(std::string, std::string, bool),
                    unsigned (*f2)(std::string, std::string, bool))
{
    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 100;

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long results[2] = { 0, 0 };
        for (unsigned k = 0; k < test_repeats; k++)
        {
            std::string s1 = random_string(size);
            std::string s2 = random_string(size);

            start_time = rdtsc();
            f1(s1, s2, false);
            end_time = rdtsc();
            results[0] += end_time - start_time;

            start_time = rdtsc();
            f2(s1, s2, false);
            end_time = rdtsc();
            results[1] += end_time - start_time;
        }
        file << size;
        for (unsigned k = 0; k < 2; k++)
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

    std::ofstream csv_matrix("report\\MatrixTime.csv");
    if (!csv_matrix.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_matrix << "Size;Leven;Damerau\n";
    time_measure(csv_matrix, 10, 70, 10, levenshtein, damerau);
    csv_matrix.close();

    std::ofstream csv_damerau("report\\DamerauTime.csv");
    if (!csv_damerau.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    csv_damerau << "Size;Matrix;Recursive\n";
    time_measure(csv_damerau, 1, 10, 1, damerau, damerau_r);
    csv_damerau.close();

    return 0;
}