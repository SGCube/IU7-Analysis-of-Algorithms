#ifndef SUBSTR_HPP
#define SUBSTR_HPP

#include <string>

int substr_std(std::string s, std::string subs);

int substr_kmp(std::string s, std::string subs);

int substr_bm(std::string s, std::string subs);

#endif
