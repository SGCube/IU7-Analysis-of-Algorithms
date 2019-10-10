#include <iostream>
#include <string>
#include <fstream>

#include "leven.hpp"

bool test(std::string &s1, std::string &s2, unsigned expected,
    unsigned (*f)(std::string, std::string, bool))
{
    unsigned got = f(s1, s2, false);
    std::cout << got << ' ';
    return (expected == got);
}

int main(void)
{
    std::string name_start = "tests\\test (";
    std::string name_end = ").txt";
    for (size_t i = 2; i <= 26; i++)
    {
        std::string s1, s2;
        unsigned expected[3];

        std::string file_name = name_start + std::to_string(i) + name_end;
        std::ifstream file(file_name);
        file >> s1;
        file >> s2;
        for (size_t k = 0; k < 3; k++)
            file >> expected[k];
        file.close();

        std::cout << "Test " << i << ": " << std::endl;
        std::cout << s1 << ' ' << s2 << std::endl;
        for (size_t k = 0; k < 3; k++)
            std::cout << expected[k] << ' ';
        std::cout << std::endl;
        std::cout << "1) Leven:\t";
        if (test(s1, s2, expected[0], levenshtein))
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        std::cout << "2) Dam-L (M):\t";
        if (test(s1, s2, expected[1], damerau))
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        std::cout << "3) Dam-L (R):\t";
        if (test(s1, s2, expected[2], damerau_r))
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        std::cout << std::endl;
    }
    return 0;
}