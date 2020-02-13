#include <cmath>
#include "substr.hpp"

#define ALPHABET_SIZE 256

int substr_std(const std::string &s, const std::string &subs)
{
    int sn = s.length(), subn = subs.length();
    int n = sn - subn + 1;
    
	for (int i = 0; i < n; i++)
	{
		bool correct = true;
		for (int j = 0; j < subn && correct; j++)
			if (subs[j] != s[i + j])
				correct = false;
		if (correct)
			return i;
	}
	return -1;
}

void fail_compute(const std::string &s, int *fail)
{
	if (s.empty())
		return;

    fail[0] = 0;
	for (unsigned i = 1, j = 0; i < s.length(); i++)
    {
        if (j > 0 && s[i] != s[j])
            j = fail[j - 1];
        if (s[i] == s[j])
            j++; 
        fail[i] = j;
    }
}

int substr_kmp(const std::string &s, const std::string &subs)
{
	if (s.empty() || subs.empty())
		return -1;

    int sn = s.length(), subn = subs.length();
	int *fail = new int[subn];
	fail_compute(subs, fail);

    int index = -1;
	for (int i = 0, j = 0; i < sn && index == -1; i++)
    {
        if (j > 0 && subs[j] != s[i])
            j = fail[j - 1];
        if (subs[j] == s[i])
            j++;
        if (j == subn)
			index = i - subn + 1;
    }
	delete [] fail;
    return index;
}

void get_slide(const std::string &subs, int *slide)
{
    if (subs.empty())
		return;
    
	int subn = subs.length();
    for (int i = 0; i < ALPHABET_SIZE; i++)
        slide[i] = subn;
    for (int i = 0; i < subn - 1; i++)
        slide[(int)subs[i]] = subn - 1 - i;
}

int substr_bm(const std::string &s, const std::string &subs)
{
    int sn = s.length(), subn = subs.length();
	int result = -1;
	int slide[ALPHABET_SIZE];
	get_slide(subs, slide);

	for(int ind = 0; ind <= sn - subn && result == -1; )
	{
        int subind = subn - 1;
        for (; subs[subind] == s[ind + subind] && result == -1; subind--)
		{
            if (subind == 0)
				result = ind;
        }
        ind += slide[(int)s[ind + subind]];
    }
	return result;
}
