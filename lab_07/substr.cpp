#include <cmath>
#include "substr.hpp"

#define SIZE 256

int substr_std(std::string s, std::string subs)
{
    int sn = s.length(), subn = subs.length();
    int n = sn - subn + 1;
    bool correct = true;

	for (int i = 0; i < n && !correct; i++)
		for (int j = 0; j < subn && correct; j++)
			if (subs[j] != s[i + j])
				correct = false;
    
    if (correct)
		return i - 1;
	return -1;
}

void fail_compute(std::string s, int n, int *fail)
{
    fail[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int j = fail[i - 1];
        while (j > 0 && s[i] != s[j])
            j = fail[j - 1];
        if (s[i] == s[j])
            j++; 
        fail[i] = j;
    }
}

int substr_kmp(std::string s, std::string subs)
{
    int sn = s.length(), subn = subs.length();
	int *fail = (int*)calloc(subn, sizeof(int));

	fail_compute(subs, subn, fail);

    int j = 0;
    for (int i = 0; i < sn; i++)
    {
        while (j > 0 && subs[j] != s[i])
            j = fail[j - 1];
        if (subs[j] == s[i])
            j++;
        if (j == subn)
		{
			delete [] fail;
            return i - subn + 1;
		}
    }
	delete [] fail;
    return -1;
}

void bad(std::string subs, int size, int *badchar)
{
	for (int i = 0; i < SIZE; i++)
		badchar[i] = -1;
	for (int i = 0; i < size; i++)
		badchar[(int)subs[i]] = i;
}

int substr_bm(std::string s, std::string subs)
{
    int sn = s.length(), subn = subs.length();
	int result = -1;
	int badchar[SIZE];
	bad(subs, subn, badchar);

	int i = 0;
	while (i <= sn - subn)
	{
		int j = subn - 1;
		while (j >= 0 && subs[j] == s[i + j])
			j--;
		if (j < 0)
		{
			result = i;
			i += (i + subn < sn) ? subn - badchar[(int)s[i + subn]] : 1;
		}
		else
			i += std::max(1, j - badchar[(int)s[i + j]]);
	}
	return result;
}
