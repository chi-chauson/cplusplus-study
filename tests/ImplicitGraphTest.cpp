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

TEST(ImplicitGraphTest, ExampleOneMutation) {
    ImplicitGraph ig;
    // "AACCGGTT" -> "AACCGGTA" is one direct mutation
    std::string start = "AACCGGTT";
    std::string end   = "AACCGGTA";
    std::vector<std::string> bank = {"AACCGGTA"};

    int result = ig.minMutation(start, end, bank);
    EXPECT_EQ(1, result);
}

TEST(ImplicitGraphTest, MultipleSteps) {
    ImplicitGraph ig;
    // Example path: AACCGGTT -> AACCGGTA -> AAACGGTA
    std::string start = "AACCGGTT";
    std::string end   = "AAACGGTA";
    std::vector<std::string> bank = {
            "AACCGGTA",
            "AAACGGTA",
            "AACCGCTA",
            "AAACGCTA"
    };

    // BFS path could be:
    //   AACCGGTT -> AACCGGTA (1 mutation)
    //   AACCGGTA -> AAACGGTA (2 mutations)
    // So expect 2
    int result = ig.minMutation(start, end, bank);
    EXPECT_EQ(2, result);
}

TEST(ImplicitGraphTest, NoPossibleMutation) {
    ImplicitGraph ig;
    // "AAAAACCC" -> "AACCCCCC" but "AACCCCCC" is NOT in the bank, unreachable
    std::string start = "AAAAACCC";
    std::string end   = "AACCCCCC";
    std::vector<std::string> bank = {
            "AAAACCCC",
            "AAACCCCC"
            // missing "AACCCCCC"
    };

    int result = ig.minMutation(start, end, bank);
    EXPECT_EQ(-1, result);
}

TEST(ImplicitGraphTest, StartEqualsEnd) {
    ImplicitGraph ig;
    // If start == end, we need 0 mutations
    std::string start = "AACCGGTT";
    std::string end   = "AACCGGTT";
    std::vector<std::string> bank = {"AACCGGTA"};
    // Bank doesn't matter here since start == end

    int result = ig.minMutation(start, end, bank);
    EXPECT_EQ(0, result);
}

TEST(ImplicitGraphTest, EndNotInBank) {
    ImplicitGraph ig;
    // Bank doesn't contain end, so there's no valid path
    std::string start = "AACCGGTT";
    std::string end   = "AACCGGTA";
    std::vector<std::string> bank = {"AAAAAACC", "GGGGGGGG"};

    int result = ig.minMutation(start, end, bank);
    EXPECT_EQ(-1, result);
}
