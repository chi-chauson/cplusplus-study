//
// Created by cchau on 2/15/2025.
//
#include <gtest/gtest.h>
#include "ImplicitGraph.h"

// A basic test for the openLock function.
TEST(ImplicitGraphTest, OpenLock_SimpleTest) {
    ImplicitGraph ig;
    std::vector<std::string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    std::string target = "0202";

    // For this setup, we expect a known answer (this is just an example).
    // If you know the solution is 6 steps from "0000" to "0202",
    // then you can compare to 6.
    int result = ig.openLock(deadends, target);
    EXPECT_EQ(result, 6);
}

TEST(ImplicitGraphTest, OpenLock_ImmediateDeadend) {
    ImplicitGraph ig;
    // "0000" is included in deadends => should return -1 immediately
    std::vector<std::string> deadends = {"0000", "1234"};
    std::string target = "9999";

    int result = ig.openLock(deadends, target);
    EXPECT_EQ(result, -1);
}

// A basic test for the calcEquation function.
TEST(ImplicitGraphTest, CalcEquation_Basic) {
    ImplicitGraph ig;

    std::vector<std::vector<std::string>> equations = {{"a", "b"},
                                                       {"b", "c"}};
    std::vector<double> values = {2.0, 3.0};
    std::vector<std::vector<std::string>> queries = {
            {"a", "c"},  // expect 6.0  (a/b=2, b/c=3 => a/c=6)
            {"b", "a"},  // expect 0.5  (b/a=1/2)
            {"a", "e"},  // expect -1.0 (unknown)
            {"a", "a"},  // expect 1.0  (trivial self-ratio)
            {"x", "x"}   // expect -1.0 (x not in graph)
    };

    auto results = ig.calcEquation(equations, values, queries);

    EXPECT_DOUBLE_EQ(results[0], 6.0);
    EXPECT_DOUBLE_EQ(results[1], 0.5);
    EXPECT_DOUBLE_EQ(results[2], -1.0);
    EXPECT_DOUBLE_EQ(results[3], 1.0);
    EXPECT_DOUBLE_EQ(results[4], -1.0);
}
