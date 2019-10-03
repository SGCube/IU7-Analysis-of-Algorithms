# Time analysing system
import random
import string
import time

import leven as lev
import damerau_leven_r as dam_r
import damerau_leven_m as dam_m

import ctypes

lib = ctypes.CDLL('time.dll')

_tick = lib.time_tick
_tick.argtypes = ()
_tick.restype = ctypes.c_ulonglong


def tick():
    return _tick()

# 0 - Levenshtein (matrix)
# 1 - Damerau-Levenshtein (matrix)
# 2 - Damerau-Levnshtein (recursive)


def time_analyse():
    max_length_to_measure = 7

    file_lev = open("TimeLeven.csv", "w")
    file_dam_m = open("TimeDamM.csv", "w")
    file_dam_r = open("TimeDamR.csv", "w")

    file_time = open("TimeResults.csv", "w")
    file_time.write("Length;Leven;DamerauM;DamerauR\n")

    for current_length in range(1, max_length_to_measure + 1):
        # Test amount definition
        measure_amount = 100

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
            start_time = tick()
            lev.str_distance(s1, s2)
            end_time = tick()
            results[0] += (end_time - start_time)

            # Damerau-Levenshtein distance time measure (matrix)
            start_time = tick()
            dam_m.str_distance(s1, s2)
            end_time = tick()
            results[1] += (end_time - start_time)

            # Damerau-Levenshtein distance time measure (recursive)
            start_time = tick()
            dam_r.str_distance(s1, s2)
            end_time = tick()
            results[2] += (end_time - start_time)

        # Average time value calculation
        for k in range(len(results)):
            results[k] = int(results[k] / measure_amount)

        print("Длина строк: ", current_length)
        print("Левенштейн (матричный): ", results[0])
        print("Даверау-Левенштейн (матричный): ", results[1])
        print("Дамерау-Левенштейн (рекурсивный): ", results[2])
        print()

        file_lev.write("%d;%d\n" % (current_length, results[0]))
        file_dam_m.write("%d;%d\n" % (current_length, results[1]))
        file_dam_r.write("%d;%d\n" % (current_length, results[2]))

        file_time.write("%d;%d;%d;%d\n" % (current_length, results[0],
                                           results[1], results[2]))

    file_lev.close()
    file_dam_m.close()
    file_dam_r.close()

    file_time.close()


if __name__ == "__main__":
    time_analyse()
