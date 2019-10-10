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

void time_measure(std::ofstream &file, unsigned start_size, unsigned end_size, unsigned step)
{
    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 100;
    file << "Size;Leven;DamerauM;DamerauR\n";

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long results[3] = { 0, 0, 0 };
        for (unsigned k = 0; k < test_repeats; k++)
        {
            std::string s1 = random_string(size);
            std::string s2 = random_string(size);

            start_time = rdtsc();
            levenshtein(s1, s2);
            end_time = rdtsc();
            results[0] += end_time - start_time;

            start_time = rdtsc();
            damerau(s1, s2);
            end_time = rdtsc();
            results[1] += end_time - start_time;

            start_time = rdtsc();
            damerau_r(s1, s2);
            end_time = rdtsc();
            results[2] += end_time - start_time;
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

    std::ofstream csv_file("TimeResults.csv");
    if (!csv_file.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    time_measure(csv_file, 1, 10, 1);
    csv_file.close();

    return 0;
}