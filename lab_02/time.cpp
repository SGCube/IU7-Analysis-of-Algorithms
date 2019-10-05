#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"
#include "vinograd.hpp"

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void time_measure(std::ofstream &file, size_t start_size, size_t end_size, size_t step)
{
    unsigned long long start_time = 0, end_time = 0;
    size_t test_repeats = 100;
    file << "Size;Classic;Vinograd;VinOptimized\n";

    for (size_t i = start_size; i <= end_size; i += step)
    {
        unsigned long long results[3] = { 0, 0, 0 };
        for (size_t k = 0; k < test_repeats; k++)
        {
            Matrix matrix_a(i, i), matrix_b(i, i);
            matrix_a.randomize(-10, 10);
            matrix_b.randomize(-10, 10);

            start_time = tick();
            Matrix matrix_c = matrix_a * matrix_b;
            end_time = tick();
            results[0] += end_time - start_time;

            start_time = tick();
            Matrix matrix_c1 = multiply_vinograd(matrix_a, matrix_b);
            end_time = tick();
            results[1] += end_time - start_time;

            start_time = tick();
            Matrix matrix_c2 = multiply_vinograd_opt(matrix_a, matrix_b);
            end_time = tick();
            results[2] += end_time - start_time;
        }
        file << i;
        for (size_t k = 0; k < 3; k++)
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

    std::ofstream csv_even("time_analyze_even.csv");
    if (!csv_even.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    time_measure(csv_even, 10, 100, 10);
    csv_even.close();

    std::ofstream csv_odd("time_analyze_odd.csv");
    if (!csv_odd.is_open())
    {
        std::cout << "File open error!";
        return -1;
    }

    time_measure(csv_odd, 11, 101, 10);
    csv_odd.close();

    return 0;
}
