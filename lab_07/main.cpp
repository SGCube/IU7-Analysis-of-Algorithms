#include <iostream>
#include <string>
#include "substr.hpp"

int main()
{
    std::string str, substr;
    std::cout << "Enter source string: ";
    std::cin >> str;
    std::cout << "Enter substring for search: ";
    std::cin >> substr;

    std::cout << "Standart: " << substr_std(str, substr) << std::endl;
	std::cout << "K-M-P: " << substr_kmp(str, substr) << std::endl;
	std::cout << "B-M: " << substr_bm(str, substr) << std::endl;

	return 0;
}