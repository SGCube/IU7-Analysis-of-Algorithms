#include <vector>

#include "levenshtein.h"

template <typename T>
void vector_print(const std::vector<T> &v)
{
	for (T data : v)
		std::cout << data << ' ';
	std::cout << std::endl;
}

// Levenshtein distance (with use of matrix)
int leven(const std::string &s1, const std::string &s2, bool toPrint)
{
	size_t s1_len = s1.length(), s2_len = s2.length();
	
	// initialization of first two rows of matrix
	std::vector<unsigned int> prev_row(s1_len + 1, 0);
	for (size_t i = 0; i <= s2_len; i++)
		prev_row[i] = i;
	std::vector<unsigned int> current_row(s2_len + 1, 0);

	// "matrix" print start
	if (toPrint)
		vector_print(prev_row);

	for (size_t i = 1; i <= s1_len; i++)			// "matrix" row loop
	{
		// current row fill with values
		current_row[0] = i;
		for (size_t j = 1; i <= s2_len; i++)		// "matrix" column loop
		{
			bool match_fault = s1[i - 1] != s2[j - 1]; // if symbols matches
			current_row[j] = std::min(current_row[j - 1] + 1, // horiz. step    
					prev_row[j] + 1,						  // vertical step
					prev_row[j - 1] + int(match_fault));	  // diagonal step
		}

		if (toPrint)							// "matrix" current row print
			vector_print(current_row);

		// row switching
		prev_row = current_row;
		current_row = std::vector<unsigned int>(s2_len + 1, 0);
	}
		  
	return prev_row[s1_len];	// value in bottom right corner of "matrix"   
}

// Damerau-Levenshtein distance (with use of matrix)
int dam_leven_m(const std::string *s1, const std::string *s2, bool toPrint)
{
	return 0;
}

// Damerau-Levenshtein distance (recursive algorythm)
int dam_level_r(std::string *s1, std::string *s2)
{
	return 0;
}
