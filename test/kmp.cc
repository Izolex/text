#include "gtest/gtest.h"
#include "../include/kmp.hh"

using namespace std;

TEST(KMP, search)
{
    string needle   = "ABCDABD";
    string haystack = "ABC ABCDAB ABCDABCDABDE";

    auto kmp = KMP::Search(needle);
    auto actual = kmp.search(haystack);
    vector<int> expected{ 15 };

    EXPECT_EQ(expected, actual);
}
