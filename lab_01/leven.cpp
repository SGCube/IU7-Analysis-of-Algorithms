#include <algorithm>
#include <string>

#include "leven.hpp"

unsigned levenshtein(std::string s1, std::string s2, bool to_print)
{
    size_t s1_len = s1.length(), s2_len = s2.length();
    size_t row_length = s2_len + 1;
    unsigned row_bytes = row_length * sizeof(unsigned);

    unsigned *prev_row = new unsigned[row_length];
    unsigned *current_row = new unsigned[row_length];
    for (size_t i = 0; i < row_length; i++)
        prev_row[i] = i;
    
    if (to_print)
    {
        for (size_t i = 0; i < row_length; i++)
            std::cout << prev_row[i] << ' ';
        std::cout << std::endl;
    }

    for (size_t i = 1; i <= s1_len; i++)
    {
        current_row[0] = i;
        for (size_t j = 0; j < row_length; j++)
        {
            unsigned match_fault = unsigned(s1[i - 1] != s2[j - 1]);
            current_row[j] = std::min({current_row[j - 1] + 1,
                                        prev_row[j] + 1,
                                        prev_row[j - 1] + match_fault});
        }
        if (to_print)
        {
            for (size_t k = 0; k < row_length; k++)
                std::cout << current_row[k] << ' ';
            std::cout << std::endl;
        }
        memcpy(prev_row, current_row, row_bytes);
    }

    unsigned result = current_row[s2_len];

    delete [] prev_row;
    delete [] current_row;

    return result;
}

unsigned damerau(std::string s1, std::string s2, bool to_print)
{
    size_t s1_len = s1.length(), s2_len = s2.length();
    size_t row_length = s2_len + 1;
    unsigned row_bytes = row_length * sizeof(unsigned);

    unsigned *prev2_row = new unsigned[row_length];
    unsigned *prev_row = new unsigned[row_length];
    unsigned *current_row = new unsigned[row_length];
    for (size_t i = 0; i < row_length; i++)
    {
        prev2_row[i] = 0;
        prev_row[i] = i;
    }
    
    if (to_print)
    {
        for (size_t i = 0; i < row_length; i++)
            std::cout << prev_row[i] << ' ';
        std::cout << std::endl;
    }

    for (size_t i = 1; i <= s1_len; i++)
    {
        current_row[0] = i;
        for (size_t j = 0; j < row_length; j++)
        {
            unsigned match_fault = unsigned(s1[i - 1] != s2[j - 1]);
            current_row[j] = std::min({current_row[j - 1] + 1,
                                        prev_row[j] + 1,
                                        prev_row[j - 1] + match_fault});
            if (i >= 2 && j >= 1)
                if (s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
                    current_row[j] = std::min(current_row[j],
                                                prev2_row[j - 2] + 1);
        }
        
        if (to_print)
        {
            for (size_t k = 0; k < row_length; k++)
                std::cout << current_row[k] << ' ';
            std::cout << std::endl;
        }

        memcpy(prev2_row, prev_row, row_bytes);
        memcpy(prev_row, current_row, row_bytes);
    }

    unsigned result = current_row[s2_len];

    delete [] prev2_row;
    delete [] prev_row;
    delete [] current_row;

    return result;
}

unsigned damerau_r(std::string s1, std::string s2, bool to_print)
{
    size_t s1_len = s1.length(), s2_len = s2.length();
    if (s1_len == 0)
        return s2_len;
    if (s2_len == 0)
        return s1_len;

    unsigned match_fault = unsigned(s1[s1_len - 1] != s2[s2_len - 1]);

    unsigned result = std::min({damerau_r(s1.substr(0, s1_len - 1),
                                          s2.substr(0, s2_len)) + 1,
                                damerau_r(s1.substr(0, s1_len),
                                          s2.substr(0, s2_len - 1)) + 1,
                                damerau_r(s1.substr(0, s1_len - 1),
                                          s2.substr(0, s2_len - 1)) + match_fault});

    if (s1_len > 1 && s2_len > 1)
        if (s1[s1_len - 1] == s2[s2_len - 2] &&
            s1[s1_len - 2] == s2[s2_len - 1])
            return std::min(result, damerau_r(s1.substr(0, s1_len - 2),
                                              s2.substr(0, s2_len - 2)) + 1);

    return result;
}

