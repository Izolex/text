#include "gtest/gtest.h"
#include "../include/ukkonen.hh"

using namespace std;

const int INF = std::numeric_limits<int>::max();

#define assertSubstring(transition, start, end) \
        EXPECT_EQ((transition)->second.first.second.first, start); \
        EXPECT_EQ((transition)->second.first.second.second, end);

TEST(Ukkonen, construction)
{
    auto ukkonen = Ukkonen::SuffixTree();
    ukkonen.addNeedle("hah");

    auto root = ukkonen.getRoot()->getTransitionMap();
    auto it = root.begin();

    auto node = it->second.second->getTransitionMap();
    auto subIt = node.begin();

    assertSubstring(it, 0, 0);
    it++;
    assertSubstring(it, 1, INF);
    it++;
    assertSubstring(it, 3, INF);

    assertSubstring(subIt, 1, INF);
    subIt++;
    assertSubstring(subIt, 3, INF);
}
