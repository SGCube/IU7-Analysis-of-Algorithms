#include <string>
#include <gtest/gtest.h>

#include "leven.hpp"


TEST(EmptyStrings, BothEmpty)
{
    std::string s1 = "";
    std::string s2 = "";
    ASSERT_EQ(0, levenshtein(s1, s2));
    ASSERT_EQ(0, damerau(s1, s2));
    ASSERT_EQ(0, damerau_r(s1, s2));
}

TEST(EmptyStrings, FirstEmpty)
{
    std::string s1 = "";
    std::string s2 = "a";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(EmptyStrings, SecondEmpty)
{
    std::string s1 = "a";
    std::string s2 = "";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(OneChar, Matched)
{
    std::string s1 = "a";
    std::string s2 = "a";
    ASSERT_EQ(0, levenshtein(s1, s2));
    ASSERT_EQ(0, damerau(s1, s2));
    ASSERT_EQ(0, damerau_r(s1, s2));
}

TEST(OneChar, Different)
{
    std::string s1 = "a";
    std::string s2 = "b";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(InsertChar, Begin)
{
    std::string s1 = "ase";
    std::string s2 = "base";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(InsertChar, Middle)
{
    std::string s1 = "mispelling";
    std::string s2 = "misspelling";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(InsertChar, End)
{
    std::string s1 = "dat";
    std::string s2 = "data";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(DeleteChar, Begin)
{
    std::string s1 = "email.ru";
    std::string s2 = "mail.ru";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(DeleteChar, Middle)
{
    std::string s1 = "programmmer";
    std::string s2 = "programmer";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(DeleteChar, End)
{
    std::string s1 = "datas";
    std::string s2 = "data";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(ReplaceChar, Begin)
{
    std::string s1 = "xode";
    std::string s2 = "code";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(ReplaceChar, Middle)
{
    std::string s1 = "hach";
    std::string s2 = "hash";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(ReplaceChar, End)
{
    std::string s1 = "date";
    std::string s2 = "data";
    ASSERT_EQ(1, levenshtein(s1, s2));
    ASSERT_EQ(1, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(TransposeChars, Begin)
{
    std::string s1 = "cxode";
    std::string s2 = "xcode";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(TransposeChars, Middle)
{
    std::string s1 = "functoin";
    std::string s2 = "function";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(TransposeChars, End)
{
    std::string s1 = "univeres";
    std::string s2 = "universe";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(1, damerau_r(s1, s2));
}

TEST(Substring, InsertBegin)
{
    std::string s1 = "header";
    std::string s2 = "subheader";
    ASSERT_EQ(3, levenshtein(s1, s2));
    ASSERT_EQ(3, damerau(s1, s2));
    ASSERT_EQ(3, damerau_r(s1, s2));
}

TEST(Substring, DeleteBegin)
{
    std::string s1 = "subheader";
    std::string s2 = "header";
    ASSERT_EQ(3, levenshtein(s1, s2));
    ASSERT_EQ(3, damerau(s1, s2));
    ASSERT_EQ(3, damerau_r(s1, s2));
}

TEST(Substring, ReplaceBegin)
{
    std::string s1 = "recoder";
    std::string s2 = "decoder";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(2, damerau_r(s1, s2));
}

TEST(Substring, InsertEnd)
{
    std::string s1 = "cour";
    std::string s2 = "course";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(2, damerau_r(s1, s2));
}

TEST(Substring, DeleteEnd)
{
    std::string s1 = "course";
    std::string s2 = "cour";
    ASSERT_EQ(2, levenshtein(s1, s2));
    ASSERT_EQ(2, damerau(s1, s2));
    ASSERT_EQ(2, damerau_r(s1, s2));
}

TEST(Substring, ReplaceEnd)
{
    std::string s1 = "scientists";
    std::string s2 = "scientific";
    ASSERT_EQ(3, levenshtein(s1, s2));
    ASSERT_EQ(3, damerau(s1, s2));
    ASSERT_EQ(3, damerau_r(s1, s2));
}

TEST(Substring, InsertBeginEnd)
{
    std::string s1 = "code";
    std::string s2 = "decoder";
    ASSERT_EQ(3, levenshtein(s1, s2));
    ASSERT_EQ(3, damerau(s1, s2));
    ASSERT_EQ(3, damerau_r(s1, s2));
}

TEST(Substring, DeleteBeginEnd)
{
    std::string s1 = "decoder";
    std::string s2 = "code";
    ASSERT_EQ(3, levenshtein(s1, s2));
    ASSERT_EQ(3, damerau(s1, s2));
    ASSERT_EQ(3, damerau_r(s1, s2));
}

TEST(Substring, ReplaceBeginEnd)
{
    std::string s1 = "decoder";
    std::string s2 = "recoding";
    ASSERT_EQ(4, levenshtein(s1, s2));
    ASSERT_EQ(4, damerau(s1, s2));
    ASSERT_EQ(4, damerau_r(s1, s2));
}

int main(void)
{
    return RUN_ALL_TESTS();
}