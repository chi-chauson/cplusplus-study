//
// Created by cchau on 12/26/2024.
//
#include "Hashing.h"
#include <gtest/gtest.h>

// Define a test fixture class if needed (optional)
class HashingTest : public ::testing::Test {
protected:
    Hashing hashing;
};

TEST_F(HashingTest, IsPangramTrue) {
    EXPECT_TRUE(hashing.checkIfPangram("thequickbrownfoxjumpsoverthelazydog"));
}

TEST_F(HashingTest, IsPangramFalse) {
    EXPECT_FALSE(hashing.checkIfPangram("leetcode"));
}

TEST_F(HashingTest, IsPangramEmpty) {
    EXPECT_FALSE(hashing.checkIfPangram(""));
}

TEST_F(HashingTest, IsPangramAlmost) {
    EXPECT_FALSE(hashing.checkIfPangram("thequickbrownfoxjumpsoverthelazyd")); //missing g
}

TEST_F(HashingTest, IsPangramDuplicateLetters) {
    EXPECT_TRUE(hashing.checkIfPangram("thequickbrownfoxjumpsoverthelazydogg")); // extra g
}

TEST_F(HashingTest, MissingNumberHashExample1) {
    EXPECT_EQ(2, hashing.missingNumber({3, 0, 1}));
}

TEST_F(HashingTest, MissingNumberHashExample2) {
    EXPECT_EQ(2, hashing.missingNumber({0, 1}));
}

TEST_F(HashingTest, MissingNumberHashExample3) {
    EXPECT_EQ(8, hashing.missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}));
}

TEST_F(HashingTest, MissingNumberHashSingleElement) {
    EXPECT_EQ(1, hashing.missingNumber({0}));
}

TEST_F(HashingTest, Example1) {
    EXPECT_EQ(2, hashing.countElements({1, 2, 3}));
}

TEST_F(HashingTest, Example2) {
    EXPECT_EQ(0, hashing.countElements({1, 1, 3, 3, 5, 5, 7, 7}));
}

TEST_F(HashingTest, WithDuplicatesAndMatch) {
    EXPECT_EQ(2, hashing.countElements({1, 1, 2}));
}

TEST_F(HashingTest, OnlyOneElement) {
    EXPECT_EQ(0, hashing.countElements({1}));
}

TEST_F(HashingTest, EmptyArray) {
    EXPECT_EQ(0, hashing.countElements({}));
}

TEST_F(HashingTest, MultipleMatches) {
    EXPECT_EQ(3, hashing.countElements({1, 2, 2, 3}));
}

TEST_F(HashingTest, LargerRange) {
    EXPECT_EQ(1, hashing.countElements({100, 200, 101}));
}

TEST_F(HashingTest, NegativeNumbers) {
    EXPECT_EQ(1, hashing.countElements({-1, 0}));
}

TEST_F(HashingTest, Example4) {
    std::vector<int> nums = {5, 7, 3, 9, 4, 9, 8, 3, 1};
    // Largest integer that occurs exactly once is 8 (since 9 appears twice).
    EXPECT_EQ(8, hashing.largestUniqueNumber(nums));
}

TEST_F(HashingTest, Example5) {
    std::vector<int> nums = {9, 9, 8, 8};
    // All numbers appear at least twice, so it should return -1.
    EXPECT_EQ(-1, hashing.largestUniqueNumber(nums));
}

TEST_F(HashingTest, SingleElement) {
    std::vector<int> nums = {10};
    // Only one element, it appears once => return 10.
    EXPECT_EQ(10, hashing.largestUniqueNumber(nums));
}

TEST_F(HashingTest, AllSame) {
    std::vector<int> nums = {4, 4, 4, 4};
    // All elements appear multiple times => -1.
    EXPECT_EQ(-1, hashing.largestUniqueNumber(nums));
}

TEST_F(HashingTest, MultipleUnique) {
    std::vector<int> nums = {0, 1, 2, 2, 1, 100, 50, 100};
    // Unique elements are {0, 50}, largest = 50
    EXPECT_EQ(50, hashing.largestUniqueNumber(nums));
}

TEST_F(HashingTest, Example6) {
    std::string text = "nlaebolko";
    // We can form "balloon" only once.
    EXPECT_EQ(1, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, Example7) {
    std::string text = "loonbalxballpoon";
    // We can form "balloon" twice.
    EXPECT_EQ(2, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, Example8) {
    std::string text = "leetcode";
    // We cannot form "balloon" => 0
    EXPECT_EQ(0, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, NoCharacters) {
    std::string text = "";
    // No characters => 0
    EXPECT_EQ(0, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, PartialCharacters) {
    std::string text = "balon";
    // Missing one 'l' and one 'o' => 0
    EXPECT_EQ(0, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, ExtraCharacters) {
    std::string text = "balloonballoonttt";
    // "balloon" can be formed 2 times
    EXPECT_EQ(2, hashing.maxNumberOfBalloons(text));
}

TEST_F(HashingTest, FindMaxLengthExample1) {
    std::vector<int> nums = {0, 1};
    // The entire array is valid => length 2
    EXPECT_EQ(2, hashing.findMaxLength(nums));
}

TEST_F(HashingTest, FindMaxLengthExample2) {
    std::vector<int> nums = {0, 1, 0};
    // [0,1] or [1,0] => length 2
    EXPECT_EQ(2, hashing.findMaxLength(nums));
}

TEST_F(HashingTest, AllZeros) {
    std::vector<int> nums = {0,0,0,0};
    // No subarray with equal 0/1 => 0
    EXPECT_EQ(0, hashing.findMaxLength(nums));
}

TEST_F(HashingTest, AllOnes) {
    std::vector<int> nums = {1,1,1,1};
    // No subarray => 0
    EXPECT_EQ(0, hashing.findMaxLength(nums));
}

TEST_F(HashingTest, Mixed) {
    // 0  1  1  0  1  1  1  0
    std::vector<int> nums = {0, 1, 1, 0, 1, 1, 1, 0};
    // One longest subarray is from index 0..3 => length = 4
    // Could be others, but 4 is the max
    EXPECT_EQ(4, hashing.findMaxLength(nums));
}