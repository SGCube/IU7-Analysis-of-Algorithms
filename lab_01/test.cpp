#include <string>
#include "gtest/gtest.h"

#include "leven.hpp"


TEST(OneChar, Matched)
{
    ASSERT_EQ(0, levenshtein("a", "a"));
    ASSERT_EQ(0, damerau("a", "a"));
    ASSERT_EQ(0, damerau_r("a", "a"));
}

TEST(OneChar, Different)
{
    ASSERT_EQ(1, levenshtein("a", "b"));
    ASSERT_EQ(1, damerau("a", "b"));
    ASSERT_EQ(1, damerau_r("a", "b"));
}

TEST(InsertChar, Begin)
{
    ASSERT_EQ(1, levenshtein("ase", "base"));
    ASSERT_EQ(1, damerau("ase", "base"));
    ASSERT_EQ(1, damerau_r("ase", "base"));
}

TEST(InsertChar, Middle)
{
    ASSERT_EQ(1, levenshtein("mispelling", "misspelling"));
    ASSERT_EQ(1, damerau("mispelling", "misspelling"));
    ASSERT_EQ(1, damerau_r("mispelling", "misspelling"));
}

TEST(InsertChar, End)
{
    ASSERT_EQ(1, levenshtein("dat", "data"));
    ASSERT_EQ(1, damerau("dat", "data"));
    ASSERT_EQ(1, damerau_r("dat", "data"));
}

TEST(DeleteChar, Begin)
{
    ASSERT_EQ(1, levenshtein("email.ru", "mail.ru"));
    ASSERT_EQ(1, damerau("email.ru", "mail.ru"));
    ASSERT_EQ(1, damerau_r("email.ru", "mail.ru"));
}

TEST(DeleteChar, Middle)
{
    ASSERT_EQ(1, levenshtein("programmmer", "programmer"));
    ASSERT_EQ(1, damerau("programmmer", "programmer"));
    ASSERT_EQ(1, damerau_r("programmmer", "programmer"));
}

TEST(DeleteChar, End)
{
    ASSERT_EQ(1, levenshtein("datas", "data"));
    ASSERT_EQ(1, damerau("datas", "data"));
    ASSERT_EQ(1, damerau_r("datas", "data"));
}

TEST(ReplaceChar, Begin)
{
    ASSERT_EQ(1, levenshtein("xode", "code"));
    ASSERT_EQ(1, damerau("xode", "code"));
    ASSERT_EQ(1, damerau_r("xode", "code"));
}

TEST(ReplaceChar, Middle)
{
    ASSERT_EQ(1, levenshtein("hach", "hash"));
    ASSERT_EQ(1, damerau("hach", "hash"));
    ASSERT_EQ(1, damerau_r("hach", "hash"));
}

TEST(ReplaceChar, End)
{
    ASSERT_EQ(1, levenshtein("date", "data"));
    ASSERT_EQ(1, damerau("date", "data"));
    ASSERT_EQ(1, damerau_r("date", "data"));
}

TEST(TransposeChars, Begin)
{
    ASSERT_EQ(2, levenshtein("cxode", "xcode"));
    ASSERT_EQ(1, damerau("cxode", "xcode"));
    ASSERT_EQ(1, damerau_r("cxode", "xcode"));
}

TEST(TransposeChars, Middle)
{
    ASSERT_EQ(2, levenshtein("functoin", "function"));
    ASSERT_EQ(1, damerau("functoin", "function"));
    ASSERT_EQ(1, damerau_r("functoin", "function"));
}

TEST(TransposeChars, End)
{
    std::string s1 = "univeres";
    std::string s2 = "universe";
    ASSERT_EQ(2, levenshtein("univeres", "universe"));
    ASSERT_EQ(1, damerau("univeres", "universe"));
    ASSERT_EQ(1, damerau_r("univeres", "universe"));
}

TEST(Substring, InsertBegin)
{
    ASSERT_EQ(3, levenshtein("header", "subheader"));
    ASSERT_EQ(3, damerau("header", "subheader"));
    ASSERT_EQ(3, damerau_r("header", "subheader"));
}

TEST(Substring, ReplaceBegin)
{
    ASSERT_EQ(2, levenshtein("encoder", "decoder"));
    ASSERT_EQ(2, damerau("encoder", "decoder"));
    ASSERT_EQ(2, damerau_r("encoder", "decoder"));
}

TEST(Substring, InsertEnd)
{
    ASSERT_EQ(2, levenshtein("cour", "course"));
    ASSERT_EQ(2, damerau("cour", "course"));
    ASSERT_EQ(2, damerau_r("cour", "course"));
}

TEST(Substring, DeleteEnd)
{
    ASSERT_EQ(2, levenshtein("course", "cour"));
    ASSERT_EQ(2, damerau("course", "cour"));
    ASSERT_EQ(2, damerau_r("course", "cour"));
}

TEST(Substring, ReplaceEnd)
{
    ASSERT_EQ(3, levenshtein("scientists", "scientific"));
    ASSERT_EQ(3, damerau("scientists", "scientific"));
    ASSERT_EQ(3, damerau_r("scientists", "scientific"));
}

TEST(Substring, InsertBeginEnd)
{
    ASSERT_EQ(3, levenshtein("code", "decoder"));
    ASSERT_EQ(3, damerau("code", "decoder"));
    ASSERT_EQ(3, damerau_r("code", "decoder"));
}

TEST(Substring, ReplaceBeginEnd)
{
    ASSERT_EQ(4, levenshtein("decoder", "recoding"));
    ASSERT_EQ(4, damerau("decoder", "recoding"));
    ASSERT_EQ(4, damerau_r("decoder", "recoding"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}