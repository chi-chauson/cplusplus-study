//
// Created by cchau on 12/25/2024.
//
#include <gtest/gtest.h>
#include "SlidingWindow.h"  // Ensure this path is correct based on your project structure

// Create a test fixture class if needed (optional)
class SlidingWindowTest : public ::testing::Test {
protected:
    // You can remove these if not needed
    SlidingWindow sw;

    void SetUp() override {
        // Code here will be called before each test
    }

    void TearDown() override {
        // Code here will be called after each test
    }
};

/**
 * Test Case 1:
 * Input: nums = [1,12,-5,-6,50,3], k = 4
 * Expected Output: 12.75000
 */
TEST_F(SlidingWindowTest, TestExample1) {
    std::vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;
    double expected = 12.75;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 1 Failed";
}

/**
 * Test Case 2:
 * Input: nums = [5], k = 1
 * Expected Output: 5.00000
 */
TEST_F(SlidingWindowTest, TestExample2) {
    std::vector<int> nums = {5};
    int k = 1;
    double expected = 5.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 2 Failed";
}

/**
 * Test Case 3:
 * Input: nums = [0,4,0,3,2], k = 1
 * Expected Output: 4.00000
 */
TEST_F(SlidingWindowTest, TestAdditional1) {
    std::vector<int> nums = {0, 4, 0, 3, 2};
    int k = 1;
    double expected = 4.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 3 Failed";
}

/**
 * Test Case 4:
 * Input: nums = [-1,-12,-5,-6,-50,-3], k = 4
 * Expected Output: -6.0
 */
TEST_F(SlidingWindowTest, TestAllNegativeNumbers) {
    std::vector<int> nums = {-1, -12, -5, -6, -50, -3};
    int k = 4;
    double expected = -6.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 4 Failed";
}

/**
 * Test Case 5:
 * Input: nums = [1,1,1,1,1,1], k = 6
 * Expected Output: 1.00000
 */
TEST_F(SlidingWindowTest, TestAllElementsSame) {
    std::vector<int> nums = {1, 1, 1, 1, 1, 1};
    int k = 6;
    double expected = 1.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 5 Failed";
}

/**
 * Test Case 6:
 * Input: nums = [10, -10, 10, -10, 10], k = 2
 * Expected Output: 0.0
 */
TEST_F(SlidingWindowTest, TestAlternatingPositiveNegative) {
    std::vector<int> nums = {10, -10, 10, -10, 10};
    int k = 2;
    double expected = 0.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 6 Failed";
}

/**
 * Test Case 7:
 * Input: nums = [1,2,3,4,5,6,7,8,9,10], k = 5
 * Expected Output: 8.0
 */
TEST_F(SlidingWindowTest, TestIncreasingSequence) {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 5;
    double expected = 8.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 7 Failed";
}

/**
 * Test Case 8:
 * Input: nums = {INT32_MAX, INT32_MAX, INT32_MAX}, k = 2
 * Expected Output: 2147483647.0
 */
TEST_F(SlidingWindowTest, TestMaxIntegerValues) {
    std::vector<int> nums = {INT32_MAX, INT32_MAX, INT32_MAX};
    int k = 2;
    double expected = static_cast<double>(INT32_MAX);
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 8 Failed";
}

/**
 * Test Case 9:
 * Input: nums = {INT32_MIN, INT32_MIN, INT32_MIN}, k = 2
 * Expected Output: -2147483648.0
 */
TEST_F(SlidingWindowTest, TestMinIntegerValues) {
    std::vector<int> nums = {INT32_MIN, INT32_MIN, INT32_MIN};
    int k = 2;
    double expected = static_cast<double>(INT32_MIN);
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 9 Failed";
}

/**
 * Test Case 10:
 * Input: nums = {100000, 100000, 100000, 100000, 100000}, k = 3
 * Expected Output: 100000.0
 */
TEST_F(SlidingWindowTest, TestLargeNumbers) {
    std::vector<int> nums = {100000, 100000, 100000, 100000, 100000};
    int k = 3;
    double expected = 100000.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 10 Failed";
}

/**
 * Test Case 11:
 * Input: nums = {1, -1, 1, -1, 1, -1, 1}, k = 3
 * Expected Output: 0.33333
 */
TEST_F(SlidingWindowTest, TestAlternatingOnes) {
    std::vector<int> nums = {1, -1, 1, -1, 1, -1, 1};
    int k = 3;
    double expected = (1 - 1 + 1) / 3.0; // ≈0.33333
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 11 Failed";
}

/**
 * Test Case 12:
 * Input: nums = {1, 2}, k = 2
 * Expected Output: 1.5
 */
TEST_F(SlidingWindowTest, TestMinimumK) {
    std::vector<int> nums = {1, 2};
    int k = 2;
    double expected = 1.5;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 12 Failed";
}

/**
 * Test Case 13:
 * Input: nums = {INT32_MAX, INT32_MIN}, k = 1
 * Expected Output: 2147483647.0
 */
TEST_F(SlidingWindowTest, TestMixedExtremeValuesK1) {
    std::vector<int> nums = {INT32_MAX, INT32_MIN};
    int k = 1;
    double expected = static_cast<double>(INT32_MAX);
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 13 Failed";
}

/**
 * Test Case 14:
 * Input: nums = {INT32_MAX, INT32_MIN}, k = 2
 * Expected Output: -0.5
 */
TEST_F(SlidingWindowTest, TestMixedExtremeValuesK2) {
    std::vector<int> nums = {INT32_MAX, INT32_MIN};
    int k = 2;
    double expected = (static_cast<double>(INT32_MAX) + static_cast<double>(INT32_MIN)) / 2.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 14 Failed";
}

/**
 * Test Case 15:
 * Input: nums = {1, 2, 3, 4, 5}, k = 5
 * Expected Output: 3.0
 */
TEST_F(SlidingWindowTest, TestFullArrayWindow) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int k = 5;
    double expected = 3.0;
    double actual = sw.findMaxAverage(nums, k);
    EXPECT_NEAR(expected, actual, 1e-5) << "Test Case 15 Failed";
}

/**
 * @brief Test Case 1:
 * Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Expected Output: 6
 * Explanation: Flipping the 0's at indices 5 and 10 yields six consecutive 1's.
 */
TEST_F(SlidingWindowTest, TestExample3) {
    std::vector<int> nums = {1,1,1,0,0,0,1,1,1,1,0};
    int k = 2;
    int expected = 6;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test Example1: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 2:
 * Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
 * Expected Output: 10
 * Explanation: Flipping the 0's at indices 4,5,10 yields ten consecutive 1's.
 */
TEST_F(SlidingWindowTest, TestExample4) {
    std::vector<int> nums = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    int k = 3;
    int expected = 10;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test Example2: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 3:
 * Input: nums = [1,1,1,1,1], k = 0
 * Expected Output: 5
 * Explanation: No flips needed as all elements are already 1.
 */
TEST_F(SlidingWindowTest, TestAllOnesNoFlips) {
    std::vector<int> nums = {1,1,1,1,1};
    int k = 0;
    int expected = 5;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test AllOnesNoFlips: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 4:
 * Input: nums = [0,0,0,0,0], k = 5
 * Expected Output: 5
 * Explanation: Flip all 0's to 1's to get five consecutive 1's.
 */
TEST_F(SlidingWindowTest, TestAllZerosWithFlips) {
    std::vector<int> nums = {0,0,0,0,0};
    int k = 5;
    int expected = 5;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test AllZerosWithFlips: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 5:
 * Input: nums = [1,0,1,0,1], k = 1
 * Expected Output: 3
 * Explanation: Flip the 0 at index 3 to get [1,0,1,1,1], which has three consecutive 1's.
 */
TEST_F(SlidingWindowTest, TestAlternatingOnesAndZeros) {
    std::vector<int> nums = {1,0,1,0,1};
    int k = 1;
    int expected = 3;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test AlternatingOnesAndZeros: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 6:
 * Input: nums = [1], k = 0
 * Expected Output: 1
 * Explanation: Single element is 1, no flips needed.
 */
TEST_F(SlidingWindowTest, TestSingleOneNoFlip) {
    std::vector<int> nums = {1};
    int k = 0;
    int expected = 1;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test SingleOneNoFlip: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 7:
 * Input: nums = [0], k = 1
 * Expected Output: 1
 * Explanation: Flip the single 0 to 1.
 */
TEST_F(SlidingWindowTest, TestSingleZeroWithFlip) {
    std::vector<int> nums = {0};
    int k = 1;
    int expected = 1;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test SingleZeroWithFlip: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 8:
 * Input: nums = [1,0,1,1,1,0,0,1,1,1,1,0,1], k = 3
 * Expected Output: 11
 * Explanation: Flip the 0's at indices 1,5,6 to get eleven consecutive 1's from index 0 to 10.
 */
TEST_F(SlidingWindowTest, TestMixedOnesAndZeros) {
    std::vector<int> nums = {1,0,1,1,1,0,0,1,1,1,1,0,1};
    int k = 3;
    int expected = 11;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test MixedOnesAndZeros: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 9:
 * Input: nums = [1,1,1,1,1,1,1,1], k = 2
 * Expected Output: 8
 * Explanation: All elements are 1, window size is 8.
 */
TEST_F(SlidingWindowTest, TestAllOnesWithFlips) {
    std::vector<int> nums = {1,1,1,1,1,1,1,1};
    int k = 2;
    int expected = 8;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test AllOnesWithFlips: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 10:
 * Input: nums = [0,1,0,1,0,1,0,1,0], k = 4
 * Expected Output: 8
 * Explanation: Flip the 0's at indices 0,2,4,6 to get eight consecutive 1's from index 0 to 7.
 */
TEST_F(SlidingWindowTest, TestFrequentFlips) {
    std::vector<int> nums = {0,1,0,1,0,1,0,1,0};
    int k = 4;
    int expected = 8;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test FrequentFlips: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 11:
 * Input: nums = [1,0,1,1,1,0,0,1,1,1,1,0,1], k = 3
 * Expected Output: 11
 * Explanation: Flip the 0's at indices 1,5,6 to get eleven consecutive 1's from index 0 to 10.
 */
TEST_F(SlidingWindowTest, TestAnotherMixedCase) {
    std::vector<int> nums = {1,0,1,1,1,0,0,1,1,1,1,0,1};
    int k = 3;
    int expected = 11;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test AnotherMixedCase: Expected " << expected << " but got " << actual;
}

/**
 * @brief Test Case 12:
 * Input: nums = [0,1,1,1,0,1,1,0,1,1,1,1,0,1,1], k = 2
 * Expected Output: 11
 * Explanation: Flip the 0's at indices 0 and 4 or 6 and 12 to get eleven consecutive 1's from index 0 to 10 or 4 to 14.
 */
TEST_F(SlidingWindowTest, TestComplexMixedCase) {
    std::vector<int> nums = {0,1,1,1,0,1,1,0,1,1,1,1,0,1,1};
    int k = 2;
    int expected = 11;
    int actual = sw.longestOnes(nums, k);
    EXPECT_EQ(actual, expected) << "Failed Test ComplexMixedCase: Expected " << expected << " but got " << actual;
}