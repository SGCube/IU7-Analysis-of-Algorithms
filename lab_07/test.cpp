#include <string>

#include "gtest/gtest.h"
#include "substr.hpp"

TEST(InMiddle, KMPSort)
{
    std::string s = "abcde", subs = "cd";
    ASSERT_TRUE(substr_kmp(s, subs) == 2);
}

TEST(InMiddle, BMSort)
{
    std::string s = "abcde", subs = "cd";
    ASSERT_TRUE(substr_bm(s, subs) == 2);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}