#include <iostream>
#include "leven.hpp"

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "-memcheck")
    {
        std::string s1 = "memcheck", s2 = "omemcpy";
        levenshtein(s1, s2, false);
        damerau(s1, s2, false);
        damerau_r(s1, s2);
        return 0;
    }
    
    std::string s1, s2;
    char c_s1[50], c_s2[50];

    std::cout << "Enter first word: ";
    std::cin >> c_s1;
    std::cout << "Enter second word: ";
    std::cin >> c_s2;

    s1 = c_s1;
    s2 = c_s2;

    std::cout << "Levenshtein:" << std::endl;
    std::cout << levenshtein(s1, s2, true) << std::endl;

    std::cout << "Damerau-Levenshtein (matrix):" << std::endl;
    std::cout << damerau(s1, s2, true) << std::endl;

    std::cout << "Damerau-Levenshtein (recursive):" << std::endl;
    std::cout << damerau_r(s1, s2) << std::endl;

    return 0;
}