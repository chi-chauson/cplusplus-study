//
// Created by cchau on 12/25/2024.
//
// PrefixSumTest.cpp
#include "PrefixSum.h"
#include <gtest/gtest.h>

// Helper function to compare two vectors
::testing::AssertionResult CompareVectors(const std::vector<int> &expected, const std::vector<int> &actual) {
    if (expected.size() != actual.size()) {
        return ::testing::AssertionFailure() << "Vectors have different sizes. Expected size: "
                                             << expected.size() << ", Actual size: " << actual.size();
    }
    for (size_t i = 0; i < expected.size(); ++i) {
        if (expected[i] != actual[i]) {
            return ::testing::AssertionFailure() << "Vectors differ at index " << i
                                                 << ". Expected: " << expected[i]
                                                 << ", Actual: " << actual[i];
        }
    }
    return ::testing::AssertionSuccess();
}

// Define a test fixture class if needed (optional)
class PrefixSumTest : public ::testing::Test {
protected:
    PrefixSum prefixSum;
};

// Test Case 1: Example 1
TEST_F(PrefixSumTest, TestExample1) {
    std::vector<int> nums = {1, 2, 3, 4};
    std::vector<int> expected = {1, 3, 6, 10};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [1, 3, 6, 10]";
}

// Test Case 2: Example 2
TEST_F(PrefixSumTest, TestExample2) {
    std::vector<int> nums = {1, 1, 1, 1, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [1, 2, 3, 4, 5]";
}

// Test Case 3: Example 3
TEST_F(PrefixSumTest, TestExample3) {
    std::vector<int> nums = {3, 1, 2, 10, 1};
    std::vector<int> expected = {3, 4, 6, 16, 17};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [3, 4, 6, 16, 17]";
}

// Test Case 4: Single Element
TEST_F(PrefixSumTest, TestSingleElement) {
    std::vector<int> nums = {5};
    std::vector<int> expected = {5};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [5]";
}

// Test Case 5: All Negative Numbers
TEST_F(PrefixSumTest, TestAllNegativeNumbers) {
    std::vector<int> nums = {-1, -2, -3, -4};
    std::vector<int> expected = {-1, -3, -6, -10};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [-1, -3, -6, -10]";
}

// Test Case 6: Mixed Positive and Negative Numbers
TEST_F(PrefixSumTest, TestMixedPositiveAndNegativeNumbers) {
    std::vector<int> nums = {1, -2, 3, -4, 5};
    std::vector<int> expected = {1, -1, 2, -2, 3};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [1, -1, 2, -2, 3]";
}

// Test Case 7: Large Numbers
TEST_F(PrefixSumTest, TestLargeNumbers) {
    std::vector<int> nums = {1000000, 2000000, 3000000};
    std::vector<int> expected = {1000000, 3000000, 6000000};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [1000000, 3000000, 6000000]";
}

// Test Case 8: Maximum Length
TEST_F(PrefixSumTest, TestMaximumLength) {
    size_t size = 1000;
    std::vector<int> nums(size, 1); // Initialize with 1000 ones
    std::vector<int> expected(size);
    expected[0] = 1;
    for (size_t i = 1; i < size; ++i) {
        expected[i] = expected[i - 1] + 1;
    }
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be an array of incremental sums up to 1000";
}

// Test Case 9: Single Negative Element
TEST_F(PrefixSumTest, TestSingleNegativeElement) {
    std::vector<int> nums = {-10};
    std::vector<int> expected = {-10};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [-10]";
}

// Test Case 10: Zeros in Array
TEST_F(PrefixSumTest, TestZerosInArray) {
    std::vector<int> nums = {0, 0, 0, 0};
    std::vector<int> expected = {0, 0, 0, 0};
    std::vector<int> result = prefixSum.runningSum(nums);
    EXPECT_TRUE(CompareVectors(expected, result)) << "Running sum should be [0, 0, 0, 0]";
}

// Example 1
TEST_F(PrefixSumTest, Example4) {
    std::vector<int> nums = {-3, 2, -3, 4, 2};
    int expected = 5;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Example 2
TEST_F(PrefixSumTest, Example5) {
    std::vector<int> nums = {1, 2};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Example 3
TEST_F(PrefixSumTest, Example6) {
    std::vector<int> nums = {1, -2, -3};
    int expected = 5;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// All Positive Numbers
TEST_F(PrefixSumTest, AllPositive) {
    std::vector<int> nums = {2, 3, 4};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// All Negative Numbers
TEST_F(PrefixSumTest, AllNegative) {
    std::vector<int> nums = {-1, -2, -3};
    int expected = 7; // 1 - (-6) = 7
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Single Positive Element
TEST_F(PrefixSumTest, SinglePositive) {
    std::vector<int> nums = {10};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Single Negative Element
TEST_F(PrefixSumTest, SingleNegative) {
    std::vector<int> nums = {-5};
    int expected = 6; // 1 - (-5) = 6
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Array with Zeros
TEST_F(PrefixSumTest, WithZeros) {
    std::vector<int> nums = {0, 0, 0};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Mixed Positive and Negative Numbers
TEST_F(PrefixSumTest, MixedNumbers) {
    std::vector<int> nums = {3, -4, 2, -3, 1};
    int expected = 3;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Large Numbers
TEST_F(PrefixSumTest, LargeNumbers) {
    std::vector<int> nums = {100, -200, 100, -100, 50};
    int expected = 101; // 1 - (-100) = 101
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Minimum Start Value One
TEST_F(PrefixSumTest, MinimumStartValueOne) {
    std::vector<int> nums = {0, 0, 1};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Additional Test: Prefix Sum Never Drops Below 1
TEST_F(PrefixSumTest, NeverDropsBelowOne) {
    std::vector<int> nums = {1, 1, 1, 1};
    int expected = 1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Additional Test: Immediate Drop Below 1
TEST_F(PrefixSumTest, ImmediateDropBelowOne) {
    std::vector<int> nums = {-1, 1};
    int expected = 2; // startValue + (-1) >=1 => startValue >=2
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Additional Test: Alternating High and Low
TEST_F(PrefixSumTest, AlternatingHighAndLow) {
    std::vector<int> nums = {5, -4, 3, -2, 1};
    // Compute prefix sums: 5,1,4,2,3
    // min_sum =1
    // startValue=1 -1=0, but since startValue must be positive, set to1
    int expected =1;
    EXPECT_EQ(prefixSum.minStartValue(nums), expected);
}

// Example 1
TEST_F(PrefixSumTest, RadiusAveragesExample1) {
    std::vector<int> nums = {7,4,3,9,1,8,5,2,6};
    int k = 3;
    std::vector<int> expected = {-1,-1,-1,5,4,4,-1,-1,-1};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Example 2
TEST_F(PrefixSumTest, RadiusAveragesExample2) {
    std::vector<int> nums = {100000};
    int k = 0;
    std::vector<int> expected = {100000};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Example 3
TEST_F(PrefixSumTest, RadiusAveragesExample3) {
    std::vector<int> nums = {8};
    int k = 100000;
    std::vector<int> expected = {-1};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// All Positive Numbers
TEST_F(PrefixSumTest, RadiusAveragesAllPositive) {
    std::vector<int> nums = {1,2,3,4,5};
    int k = 1;
    std::vector<int> expected = {-1,2,3,4,-1};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// All Negative Numbers
TEST_F(PrefixSumTest, RadiusAveragesAllNegative) {
    std::vector<int> nums = {-1,-2,-3,-4,-5};
    int k = 2;
    std::vector<int> expected = {-1,-1,-3,-1,-1};
    // Explanation: Only index 2 has enough elements on both sides.
    // Sum = (-1)+(-2)+(-3)+(-4)+(-5) = -15
    // Average = -15 /5 = -3
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Single Positive Element
TEST_F(PrefixSumTest, RadiusAveragesSinglePositive) {
    std::vector<int> nums = {10};
    int k = 0;
    std::vector<int> expected = {10};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Single Negative Element
TEST_F(PrefixSumTest, RadiusAveragesSingleNegative) {
    std::vector<int> nums = {-5};
    int k = 0;
    std::vector<int> expected = {-5};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Array with Zeros
TEST_F(PrefixSumTest, RadiusAveragesWithZeros) {
    std::vector<int> nums = {0, 0, 0, 0, 0};
    int k = 2;
    std::vector<int> expected = {-1,-1,0,-1,-1};
    // Sum at index 2: 0+0+0+0+0=0, Average=0/5=0
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Mixed Positive and Negative Numbers
TEST_F(PrefixSumTest, RadiusAveragesMixedNumbers) {
    std::vector<int> nums = {3, -4, 2, -3, 1};
    int k = 1;
    std::vector<int> expected = {-1,0,-1,0,-1};
    // Explanation:
    // Index0: -1
    // Index1: (3 -4 +2) /3 =1/3=0
    // Index2: (-4 +2 -3)/3=-5/3=-1
    // Index3: (2 -3 +1)/3=0/3=0
    // Index4: -1
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Large K
TEST_F(PrefixSumTest, RadiusAveragesLargeK) {
    std::vector<int> nums = {1,2,3};
    int k = 100;
    std::vector<int> expected = {-1,-1,-1};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// K Zero
TEST_F(PrefixSumTest, RadiusAveragesKZero) {
    std::vector<int> nums = {5, -3, 7, 0};
    int k = 0;
    std::vector<int> expected = {5, -3, 7, 0};
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}

// Even Length Array
TEST_F(PrefixSumTest, RadiusAveragesEvenLength) {
    std::vector<int> nums = {1,2,3,4,5,6};
    int k = 2;
    std::vector<int> expected = {-1,-1,3,4,-1,-1};
    // Explanation:
    // Index0: -1
    // Index1: -1
    // Index2: (1+2+3+4+5)/5=15/5=3
    // Index3: (2+3+4+5+6)/5=20/5=4
    // Index4: -1
    // Index5: -1
    EXPECT_EQ(prefixSum.getAverages(nums, k), expected);
}