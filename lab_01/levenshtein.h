#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>

// Levenshtein distance (with use of matrix)
int leven(const std::string &s1, const std::string &s2, bool toPrint);

// Damerau-Levenshtein distance (with use of matrix)
int dam_leven_m(const std::string &s1, const std::string &s2, bool toPrint);

// Damerau-Levenshtein distance (recursive algorythm)
int dam_level_r(const std::string &s1, const std::string &s2);

#endif // LEVENSHTEIN_H
