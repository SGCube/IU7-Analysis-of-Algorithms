#ifndef SUBSTR_HPP
#define SUBSTR_HPP

#include <string>

int substr_std(const std::string &s, const std::string &subs);

int substr_kmp(const std::string &s, const std::string &subs);

int substr_bm(const std::string &s, const std::string &subs);

#endif
