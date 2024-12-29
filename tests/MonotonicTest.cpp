//
// Created by cchau on 12/29/2024.
//

#include "gtest/gtest.h"
#include "Monotonic.h"

class MonotonicTest : public ::testing::Test {
protected:
    Monotonic monotonic;
};

TEST_F(MonotonicTest, Example1) {
    std::vector<int> nums1 = {4, 1, 2};
    std::vector<int> nums2 = {1, 3, 4, 2};
    std::vector<int> expected = {-1, 3, -1};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, Example2) {
    std::vector<int> nums1 = {2, 4};
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::vector<int> expected = {3, -1};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, NoGreaterElements) {
    std::vector<int> nums1 = {4, 3, 2, 1};
    std::vector<int> nums2 = {1, 2, 3, 4, 5};
    std::vector<int> expected = {5, 4, 3, 2};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, SingleElementNoGreater) {
    std::vector<int> nums1 = {4};
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::vector<int> expected = {-1};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, SingleElementWithGreater) {
    std::vector<int> nums1 = {2};
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::vector<int> expected = {3};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, MultipleElementsSomeWithGreater) {
    std::vector<int> nums1 = {1, 3};
    std::vector<int> nums2 = {1, 2, 3, 4};
    std::vector<int> expected = {2, 4};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, EmptyNums1) {
    std::vector<int> nums1 = {};
    std::vector<int> nums2 = {1, 2, 3};
    std::vector<int> expected = {};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, LargeInput) {
    std::vector<int> nums1(500);
    std::vector<int> nums2(1000);
    std::vector<int> expected(500);

    for (int i = 0; i < 500; i++) {
        nums1[i] = i;
        nums2[i] = i;
        expected[i] = i + 1;
    }
    for(int i = 500; i < 1000; i++) {
        nums2[i] = i;
    }
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, LargeInput2) {
    std::vector<int> nums1(500);
    std::vector<int> nums2(1000);
    std::vector<int> expected(500);

    for (int i = 0; i < 500; ++i) {
        nums1[i] = i*2;
        nums2[i*2] = i*2;
        nums2[i*2+1] = i*2+1;
        expected[i] = i*2+1;
    }
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}

TEST_F(MonotonicTest, Nums1SubsetAtEndNums2) {
    std::vector<int> nums1 = {2,3,4};
    std::vector<int> nums2 = {1,2,3,4};
    std::vector<int> expected = {3,4,-1};
    ASSERT_EQ(monotonic.nextGreaterElement(nums1, nums2), expected);
}