#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "substr.hpp"

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

std::string rand_str(unsigned n)
{
    std::string s;
    for (unsigned i = 0; i < n; i++)
        s += rand() % 26 + 'a';
    return s;
}

void time_measure(std::ofstream &file, unsigned start_size,
                    unsigned end_size, unsigned step)
{
    if (start_size < 2)
        return;

    unsigned long long start_time = 0, end_time = 0;
    unsigned test_repeats = 100;
    file << "Size;Std;KMP;BM" << std::endl;

    for (unsigned size = start_size; size <= end_size; size += step)
    {
        unsigned long long result[3] = { 0, 0, 0 };
        for (unsigned k = 0; k < test_repeats; k++)
        {
            std::string s = rand_str(size);
            std::string subs;
            subs += s[size / 2];
            subs += s[size / 2 + 1];

            start_time = rdtsc();
            substr_std(s, subs);
            end_time = rdtsc();
            result[0] += end_time - start_time;

            start_time = rdtsc();
            substr_kmp(s, subs);
            end_time = rdtsc();
            result[1] += end_time - start_time;

            start_time = rdtsc();
            substr_bm(s, subs);
            end_time = rdtsc();
            result[2] += end_time - start_time;
        }

        file << size;
        for (unsigned k = 0; k < 3; k++)
        {
            result[k] /= test_repeats;
            file << ";" << result[k];
        }
        file << std::endl;
    }
}

int main(void)
{
    srand(time(NULL));
    std::ofstream csv("report/time.csv");
    if (!csv.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }
    time_measure(csv, 10, 200, 10);
    csv.close();

    return 0;
}
