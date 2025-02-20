//
// Created by cchau on 2/18/2025.
//
#include <gtest/gtest.h>
#include "HeapUtil.h"

class HeapUtilTest : public ::testing::Test {
protected:
    HeapUtil heapUtil;

    // Common setup for each test (optional)
    void SetUp() override {
        // Code here runs before each test.
    }

    // Common teardown for each test (optional)
    void TearDown() override {
        // Code here runs after each test.
    }
};

TEST_F(HeapUtilTest, Example1) {
    // Input: piles = [5, 4, 9], k = 2
    // Expected Output: 12
    std::vector<int> piles = {5, 4, 9};
    int k = 2;
    int result = heapUtil.minStoneSum(piles, k);
    EXPECT_EQ(12, result);
}

TEST_F(HeapUtilTest, Example2) {
    // Input: piles = [4, 3, 6, 7], k = 3
    // Expected Output: 12
    std::vector<int> piles = {4, 3, 6, 7};
    int k = 3;
    int result = heapUtil.minStoneSum(piles, k);
    EXPECT_EQ(12, result);
}

TEST_F(HeapUtilTest, SinglePileTest) {
    // Single pile = 10, k = 5
    // Iteration of changes:
    // 10 -> 5 -> 3 -> 2 -> 1 -> 1
    // Final sum = 1
    std::vector<int> piles = {10};
    int k = 5;
    int result = heapUtil.minStoneSum(piles, k);
    EXPECT_EQ(1, result);
}

TEST_F(HeapUtilTest, AlreadySmallPilesTest) {
    // piles = [1, 1, 1], k = 10
    // Removing floor(1/2) = 0 stones means each remains 1
    // Final sum = 3
    std::vector<int> piles = {1, 1, 1};
    int k = 10;
    int result = heapUtil.minStoneSum(piles, k);
    EXPECT_EQ(3, result);
}

TEST_F(HeapUtilTest, LargerRandomTest) {
    // Example: piles = [10, 15, 20], k = 3
    // The max-heap sequence of operations:
    //   - Pick 20: becomes 10 -> [10, 15, 10]
    //   - Pick 15: becomes 8  -> [10, 10, 8]
    //   - Pick 10: becomes 5  -> [10, 8, 5]
    // Final sum = 10 + 8 + 5 = 23
    std::vector<int> piles = {10, 15, 20};
    int k = 3;
    int result = heapUtil.minStoneSum(piles, k);
    EXPECT_EQ(23, result);
}