# Testing system
from os import listdir
import leven as lev
import damerau_leven_r as dam_r
import damerau_leven_m as dam_m


def test():
    # load all test files
    file_list = listdir("tests/")

    for test_no in range(len(file_list)):
        file = open("tests/" + file_list[test_no], 'r')
        print("Test #", test_no, sep="")

        # read strings
        s1 = file.readline().strip()
        print("String 1: ", s1)
        s2 = file.readline().strip()
        print("String 2: ", s2)

        # read expected results
        expected = list(map(int, file.readline().split(' ')))
        print("Expected:", end=' ')
        for i in range(3):
            print(expected[i], end=' ')

        # do test
        got = [lev.str_distance(s1, s2),
               dam_m.str_distance(s1, s2),
               dam_r.str_distance(s1, s2)]
        print("\nGot:", end=' ')
        for i in range(3):
            print(got[i], end=' ')

        # result definition
        result = True
        i = 0
        while result and i < len(expected):
            result = (expected[i] == got[i])
            i += 1
        print("\nResult: ", "PASSED\n" if result else "FAILED\n")

        expected.clear()
        got.clear()
        file.close()


if __name__ == "__main__":
    test()
