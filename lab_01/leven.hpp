#ifndef LEVEN_HPP
#define LEVEN_HPP
#include <iostream>

unsigned levenshtein(std::string s1, std::string s2, bool to_print=false);

unsigned damerau(std::string s1, std::string s2, bool to_print=false);

unsigned damerau_r(std::string s1, std::string s2, bool to_print=false);

#endif