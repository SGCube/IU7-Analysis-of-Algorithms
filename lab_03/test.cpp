#include <cstring>

#include "gtest/gtest.h"
#include "array.hpp"

TEST(OneElement, InsertSort)
{
    int source[1] = { 1 };
    int sorted[1] = { 1 };
    array_sort_insert(source, 1);
    ASSERT_TRUE(memcmp(source, sorted, sizeof(int)) == 0 );
}

TEST(OneElement, MergeSort)
{
    int source[1] = { 1 };
    int sorted[1] = { 1 };
    array_sort_merge(source, 0, 0);
    ASSERT_TRUE(memcmp(source, sorted, sizeof(int)) == 0 );
}

TEST(OneElement, QuickSort)
{
    int source[1] = { 1 };
    int sorted[1] = { 1 };
    array_sort_quick(source, 0, 0);
    ASSERT_TRUE(memcmp(source, sorted, sizeof(int)) == 0 );
}

TEST(AlreadySorted, InsertSort)
{
    int source[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_insert(source, 10);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(AlreadySorted, MergeSort)
{
    int source[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_merge(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(AlreadySorted, QuickSort)
{
    int source[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_quick(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(InverseSorted, InsertSort)
{
    int source[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_insert(source, 10);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(InverseSorted, MergeSort)
{
    int source[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_merge(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(InverseSorted, QuickSort)
{
    int source[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int sorted[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    array_sort_quick(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(AllSame, InsertSort)
{
    int source[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int sorted[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    array_sort_insert(source, 10);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(AllSame, MergeSort)
{
    int source[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int sorted[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    array_sort_merge(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(AllSame, QuickSort)
{
    int source[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int sorted[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    array_sort_quick(source, 0, 9);
    ASSERT_TRUE(memcmp(source, sorted, 10 * sizeof(int)) == 0 );
}

TEST(SomeSame, InsertSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 4 };
    int sorted[6] = { -1, 0, 2, 4, 4, 5 };
    array_sort_insert(source, 6);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

TEST(SomeSame, MergeSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 4 };
    int sorted[6] = { -1, 0, 2, 4, 4, 5 };
    array_sort_merge(source, 0, 5);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

TEST(SomeSame, QuickSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 4 };
    int sorted[6] = { -1, 0, 2, 4, 4, 5 };
    array_sort_quick(source, 0, 5);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

TEST(NoSame, InsertSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 3 };
    int sorted[6] = { -1, 0, 2, 3, 4, 5 };
    array_sort_insert(source, 6);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

TEST(NoSame, MergeSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 3 };
    int sorted[6] = { -1, 0, 2, 3, 4, 5 };
    array_sort_merge(source, 0, 5);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

TEST(NoSame, QuickSort)
{
    int source[6] = { 5, 4, 0, 2, -1, 3 };
    int sorted[6] = { -1, 0, 2, 3, 4, 5 };
    array_sort_quick(source, 0, 5);
    ASSERT_TRUE(memcmp(source, sorted, 6 * sizeof(int)) == 0 );
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}