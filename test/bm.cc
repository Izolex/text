#include "gtest/gtest.h"
#include "../include/bm.hh"

using namespace std;

TEST(BoyerMoore, search)
{
    string needle   = "CCTTTTGC";
    string haystack = "GCTTCTGCTACCTTTTGCGCGCGCGCGGAA";

    auto bm = BoyerMoore::Search(needle);
    auto actual = bm.search(haystack);
    vector<int> expected{ 17 };

    EXPECT_EQ(expected, actual);
}
