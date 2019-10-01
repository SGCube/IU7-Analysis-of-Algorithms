# Time analysing system
import random
import string
import time

import leven as lev
import damerau_leven_r as dam_r
import damerau_leven_m as dam_m

# 0 - Levenshtein (matrix)
# 1 - Damerau-Levenshtein (matrix)
# 2 - Damerau-Levnshtein (recursive)


def time_analyse():
    ticks_per_ms = 100 / time.get_clock_info("process_time").resolution

    max_length_to_measure = 10

    file_lev = open("time_leven.txt", "w")
    file_dam_m = open("time_dam_m.txt", "w")
    file_dam_r = open("time_dam_r.txt", "w")

    for current_length in range(1, max_length_to_measure + 1):
        # Test amount definition
        measure_amount = 1000
        if current_length > 6:
            measure_amount = 1
        elif current_length > 4:
            measure_amount = 10

        # Time measure results
        results = [0, 0, 0]

        # Time measure
        for k in range(measure_amount):
            # Strings generation
            s1 = ''.join(random.choice(string.ascii_lowercase)
                         for j in range(current_length))
            s2 = ''.join(random.choice(string.ascii_lowercase)
                         for j in range(current_length))

            # Levenshtein distance time measure
            start_time = time.perf_counter()
            lev.str_distance(s1, s2)
            end_time = time.perf_counter()
            results[0] = end_time - start_time

            # Damerau-Levenshtein distance time measure (matrix)
            start_time = time.perf_counter()
            dam_m.str_distance(s1, s2)
            end_time = time.perf_counter()
            results[1] = end_time - start_time

            # Damerau-Levenshtein distance time measure (recursive)
            start_time = time.perf_counter()
            dam_r.str_distance(s1, s2)
            end_time = time.perf_counter()
            results[2] = end_time - start_time

        # Average time value calculation
        for k in range(len(results)):
            results[k] = int(results[k] / measure_amount * ticks_per_ms)

        print("Длина строк: ", current_length)
        print("Левенштейн (матричный): ", results[0])
        print("Даверау-Левенштейн (матричный): ", results[1])
        print("Дамерау-Левенштейн (рекурсивный): ", results[2])
        print()

        file_lev.write("(%d,%d) " % (current_length, results[0]))
        file_dam_m.write("(%d,%d) " % (current_length, results[1]))
        file_dam_r.write("(%d,%d) " % (current_length, results[2]))

    file_lev.close()
    file_dam_m.close()
    file_dam_r.close()


if __name__ == "__main__":
    time_analyse()
