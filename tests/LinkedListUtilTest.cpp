//
// Created by cchau on 12/27/2024.
//
#include "LinkedListUtil.h"
#include <gtest/gtest.h>

class LinkedListUtilTest : public ::testing::Test {
protected:
    LinkedListUtil util;

    ListNode *createLinkedList(const std::vector<int> &values) {
        if (values.empty()) {
            return nullptr;
        }

        ListNode *head = new ListNode(values[0]);
        ListNode *current = head;
        for (size_t i = 1; i < values.size(); ++i) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
        return head;
    }

    std::vector<int> linkedListToVector(ListNode *head) {
        std::vector<int> result;
        while (head) {
            result.push_back(head->val);
            head = head->next;
        }
        return result;
    }

    void deleteLinkedList(ListNode *head) {
        while (head) {
            ListNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Helper function to compare two vectors
    bool compareVectors(const std::vector<int>& a, const std::vector<int>& b) {
        return a == b;
    }
};

TEST_F(LinkedListUtilTest, MiddleNodeOddLength) {
    ListNode *head = createLinkedList({1, 2, 3, 4, 5});
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(3, middle->val);
    deleteLinkedList(head);
}

TEST_F(LinkedListUtilTest, MiddleNodeEvenLength) {
    ListNode *head = createLinkedList({1, 2, 3, 4, 5, 6});
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(4, middle->val);
    deleteLinkedList(head);
}

TEST_F(LinkedListUtilTest, MiddleNodeSingleNode) {
    ListNode *head = new ListNode(1);
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(1, middle->val);
    delete head;
}

TEST_F(LinkedListUtilTest, MiddleNodeEmptyList) {
    ListNode *head = nullptr;
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(nullptr, middle);
}

TEST_F(LinkedListUtilTest, MiddleNodeTwoNodes) {
    ListNode *head = createLinkedList({1, 2});
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(2, middle->val);
    deleteLinkedList(head);
}

TEST_F(LinkedListUtilTest, MiddleNodeLongList) {
    ListNode *head = createLinkedList({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    ListNode *middle = util.middleNode(head);
    ASSERT_EQ(6, middle->val);
    deleteLinkedList(head);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_EmptyList) {
    ListNode *head = nullptr;
    ListNode *result = util.deleteDuplicates(head);
    ASSERT_EQ(nullptr, result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_SingleNode) {
    ListNode *head = new ListNode(1);
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {1};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_NoDuplicates) {
    ListNode *head = createLinkedList({1, 2, 3, 4, 5});
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_AllDuplicates) {
    ListNode *head = createLinkedList({1, 1, 1, 1, 1});
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {1};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_MixedDuplicates) {
    ListNode *head = createLinkedList({1, 1, 2, 3, 3});
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {1, 2, 3};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_ConsecutiveDuplicates) {
    ListNode *head = createLinkedList({1, 2, 2, 3, 4, 4, 4, 5});
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, RemoveDuplicates_NegativeValues) {
    ListNode *head = createLinkedList({-3, -3, -2, -1, -1, 0, 1, 1, 2});
    ListNode *result = util.deleteDuplicates(head);
    std::vector<int> expected = {-3, -2, -1, 0, 1, 2};
    ASSERT_EQ(expected, linkedListToVector(result));
    deleteLinkedList(result);
}

// Test Case 1: Example 1
TEST_F(LinkedListUtilTest, ReverseBetween_Example1) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 2, right = 4;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {1, 4, 3, 2, 5};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseBetween_Example2) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 1, right = 5;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {5, 4, 3, 2, 1};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseSingleElementMiddle) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 3, right = 3;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseFirstTwoElements) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 1, right = 2;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {2, 1, 3, 4, 5};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseLastTwoElements) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 4, right = 5;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {1, 2, 3, 5, 4};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, SingleNodeLeftNotEqualRight) {
    std::vector<int> input = {1};
    int left = 1, right = 1;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {1};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseMiddleSection) {
    std::vector<int> input = {1, 2, 3, 4, 5, 6};
    int left = 2, right = 5;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {1, 5, 4, 3, 2, 6};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseFromHead) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    int left = 1, right = 3;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {3, 2, 1, 4, 5};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}

TEST_F(LinkedListUtilTest, ReverseTwoNodeList) {
    std::vector<int> input = {1, 2};
    int left = 1, right = 2;
    ListNode* head = createLinkedList(input);
    ListNode* result = util.reverseBetween(head, left, right);
    std::vector<int> expected = {2, 1};
    EXPECT_TRUE(compareVectors(linkedListToVector(result), expected));
    deleteLinkedList(result);
}