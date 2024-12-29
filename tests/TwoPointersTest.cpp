//
// Created by cchau on 12/24/2024.
//

#include <gtest/gtest.h>
#include "TwoPointers.h"
#include <vector>

// Fixture for TwoPointers tests
class TwoPointersTest : public ::testing::Test {
protected:
    TwoPointers util;
};

// Test reversing an empty string
TEST_F(TwoPointersTest, ReverseEmptyString) {
    std::vector<char> input = {};
    std::vector<char> expected = {};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "Reversing an empty array should result in an empty array.";
}

// Test reversing a single character
TEST_F(TwoPointersTest, ReverseSingleCharacter) {
    std::vector<char> input = {'a'};
    std::vector<char> expected = {'a'};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "Reversing a single-character array should result in the same array.";
}

// Test reversing an even-length string
TEST_F(TwoPointersTest, ReverseEvenLengthString) {
    std::vector<char> input = {'h', 'e', 'l', 'l', 'o', '!', '!'};
    std::vector<char> expected = {'!', '!', 'o', 'l', 'l', 'e', 'h'};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "The array should be reversed correctly for even-length strings.";
}

// Test reversing an odd-length string
TEST_F(TwoPointersTest, ReverseOddLengthString) {
    std::vector<char> input = {'J', 'u', 'n', 'i', 't'};
    std::vector<char> expected = {'t', 'i', 'n', 'u', 'J'};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "The array should be reversed correctly for odd-length strings.";
}

// Test reversing a string with spaces
TEST_F(TwoPointersTest, ReverseStringWithSpaces) {
    std::vector<char> input = {' ', 'a', ' ', 'b', ' '};
    std::vector<char> expected = {' ', 'b', ' ', 'a', ' '};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "The array with spaces should be reversed correctly.";
}

// Test reversing a string with special characters
TEST_F(TwoPointersTest, ReverseStringWithSpecialCharacters) {
    std::vector<char> input = {'@', '#', '$', '%', '^'};
    std::vector<char> expected = {'^', '%', '$', '#', '@'};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "The array with special characters should be reversed correctly.";
}

// Test reversing an already reversed string
TEST_F(TwoPointersTest, ReverseAlreadyReversedString) {
    std::vector<char> input = {'d', 'l', 'r', 'o', 'w'};
    std::vector<char> expected = {'w', 'o', 'r', 'l', 'd'};
    util.reverseString(input);
    EXPECT_EQ(input, expected) << "Reversing an already reversed array should yield the original array.";
}

// Test Example 1
TEST_F(TwoPointersTest, Example1) {
    std::vector<int> nums = {-4, -1, 0, 3, 10};
    std::vector<int> expected = {0, 1, 9, 16, 100};

    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test Example 2
TEST_F(TwoPointersTest, Example2) {
    std::vector<int> nums = {-7, -3, 2, 3, 11};
    std::vector<int> expected = {4, 9, 9, 49, 121};

    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test All Positive Numbers
TEST_F(TwoPointersTest, AllPositive) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 4, 9, 16, 25};
    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test All Negative Numbers
TEST_F(TwoPointersTest, AllNegative) {
    std::vector<int> nums = {-5, -4, -3, -2, -1};
    std::vector<int> expected = {1, 4, 9, 16, 25};
    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test Single Element
TEST_F(TwoPointersTest, SingleElement) {
    std::vector<int> nums = {-1};
    std::vector<int> expected = {1};
    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test All Zeros
TEST_F(TwoPointersTest, AllZeros) {
    std::vector<int> nums = {0, 0, 0};
    std::vector<int> expected = {0, 0, 0};
    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}

// Test Mixed Values
TEST_F(TwoPointersTest, MixedValues) {
    std::vector<int> nums = {-3, -1, 0, 1, 2};
    std::vector<int> expected = {0, 1, 1, 4, 9};
    // Two-Pointer Technique
    std::vector<int> resultTwoPointer = util.sortedSquares(nums);
    EXPECT_EQ(resultTwoPointer, expected) << "Two-Pointer: Output does not match expected.";

}