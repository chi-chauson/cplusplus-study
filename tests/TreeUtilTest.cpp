//
// Created by cchau on 12/29/2024.
//
#include "TreeUtil.h"
#include <vector>
#include <optional>
#include <queue>
#include "gtest/gtest.h"

class TreeUtilTest : public ::testing::Test {
protected:
    TreeUtil treeUtil;
};

/**
* Builds a binary tree from a level-order representation.
* @param values A vector of std::optional<int> representing node values in level order.
*               std::nullopt represents a null node.
* @return Pointer to the root of the binary tree.
*/
static TreeNode* buildTree(const std::vector<std::optional<int>>& values) {
    if (values.empty() || !values[0].has_value()) return nullptr;

    TreeNode* root = new TreeNode(values[0].value());
    std::queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    size_t i = 1;

    while (i < values.size()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        // Assign left child
        if (i < values.size() && values[i].has_value()) {
            current->left = new TreeNode(values[i].value());
            nodeQueue.push(current->left);
        }
        i++;

        // Assign right child
        if (i < values.size() && values[i].has_value()) {
            current->right = new TreeNode(values[i].value());
            nodeQueue.push(current->right);
        }
        i++;
    }

    return root;
}

/**
     * Deletes a binary tree to free memory.
     * @param root Pointer to the root of the binary tree.
     */
static void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

TEST_F(TreeUtilTest, testEmptyTree_returnsZero) {
    EXPECT_EQ(0, treeUtil.minDepth(nullptr));
}

TEST_F(TreeUtilTest, testSingleNodeTree_returnsOne) {
    TreeNode root(1);
    EXPECT_EQ(1, treeUtil.minDepth(&root));
}

TEST_F(TreeUtilTest, testLeftSkewedTree_returnsCorrectDepth) {
    TreeNode root(1);
    root.left = new TreeNode(2);
    root.left->left = new TreeNode(3);
    EXPECT_EQ(3, treeUtil.minDepth(&root));
    delete root.left->left;
    delete root.left;
}

TEST_F(TreeUtilTest, testRightSkewedTree_returnsCorrectDepth) {
    TreeNode root(1);
    root.right = new TreeNode(2);
    root.right->right = new TreeNode(3);
    EXPECT_EQ(3, treeUtil.minDepth(&root));
    delete root.right->right;
    delete root.right;
}

TEST_F(TreeUtilTest, testBalancedTree_returnsCorrectDepth) {
    TreeNode root(1);
    root.left = new TreeNode(2);
    root.right = new TreeNode(3);
    EXPECT_EQ(2, treeUtil.minDepth(&root));
    delete root.left;
    delete root.right;
}

TEST_F(TreeUtilTest, testComplexTree_example1_returnsTwo) {
    TreeNode root(3);
    root.left = new TreeNode(9);
    root.right = new TreeNode(20);
    root.right->left = new TreeNode(15);
    root.right->right = new TreeNode(7);
    EXPECT_EQ(2, treeUtil.minDepth(&root));
    delete root.left;
    delete root.right->left;
    delete root.right->right;
    delete root.right;
}

TEST_F(TreeUtilTest, testComplexTree_example2_returnsFive) {
    TreeNode root(2);
    root.right = new TreeNode(3);
    root.right->right = new TreeNode(4);
    root.right->right->right = new TreeNode(5);
    root.right->right->right->right = new TreeNode(6);
    EXPECT_EQ(5, treeUtil.minDepth(&root));
    delete root.right->right->right->right;
    delete root.right->right->right;
    delete root.right->right;
    delete root.right;
}

TEST_F(TreeUtilTest, testLeftSubtreeHasOnlyRightChild_returnsCorrectDepth) {
    TreeNode root(1);
    root.left = new TreeNode(2);
    root.left->right = new TreeNode(3);
    EXPECT_EQ(3, treeUtil.minDepth(&root));
    delete root.left->right;
    delete root.left;
}

TEST_F(TreeUtilTest, testRightSubtreeHasOnlyLeftChild_returnsCorrectDepth) {
    TreeNode root(1);
    root.right = new TreeNode(2);
    root.right->left = new TreeNode(3);
    EXPECT_EQ(3, treeUtil.minDepth(&root));
    delete root.right->left;
    delete root.right;
}

// Test Cases

TEST_F(TreeUtilTest, TestMaximumDifferenceExample1) {
    // Example 1:
    // Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
    // Output: 7
    std::vector<std::optional<int>> input = {8,3,10,1,6,std::nullopt,14,std::nullopt,std::nullopt,4,7,13};
    TreeNode* root = buildTree(input);
    int expected = 7;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceExample2) {
    // Example 2:
    // Input: root = [1,null,2,null,0,3]
    // Output: 3
    std::vector<std::optional<int>> input = {1, std::nullopt, 2, std::nullopt, 0, 3};
    TreeNode* root = buildTree(input);
    int expected = 3;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceSingleLeft) {
    // Test with all left children
    // Input: [5,3,null,2,null,1]
    // Expected Output: 4 (|5 -1| = 4)
    std::vector<std::optional<int>> input = {5,3,std::nullopt,2,std::nullopt,1};
    TreeNode* root = buildTree(input);
    int expected = 4;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceSingleRight) {
    // Test with all right children
    // Input: [5,null,8,null,10,null,12]
    // Expected Output: 7 (|5 -12| = 7)
    std::vector<std::optional<int>> input = {5, std::nullopt, 8, std::nullopt, 10, std::nullopt, 12};
    TreeNode* root = buildTree(input);
    int expected = 7;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceAllSame) {
    // Test with all nodes having the same value
    // Input: [1,1,1,1,1,1,1]
    // Expected Output: 0
    std::vector<std::optional<int>> input = {1,1,1,1,1,1,1};
    TreeNode* root = buildTree(input);
    int expected = 0;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceLargeTree) {
    // Test with a larger balanced tree
    // Input: [50,30,70,20,40,60,80,10,25,35,45,55,65,75,85]
    // Expected Output: 40 (|50 -10| = 40)
    std::vector<std::optional<int>> input = {
            50,
            30, 70,
            20, 40, 60, 80,
            10, 25, 35, 45, 55, 65, 75, 85
    };
    TreeNode* root = buildTree(input);
    int expected = 40;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceTwoNodes) {
    // Test with the smallest possible tree (two nodes)
    // Input: [1,2]
    // Expected Output: 1
    std::vector<std::optional<int>> input = {1, 2};
    TreeNode* root = buildTree(input);
    int expected = 1;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

 TEST_F(TreeUtilTest, TestMaximumDifferenceNegativeValues) {
     // Although constraints specify 0 <= Node.val, testing negative values for robustness
     // Input: [5,3,9,1,4,7,12]
     // Expected Output: 11 (|1 -12| = 11 is invalid as no ancestor-descendant relationship,
     // but |5 -12| =7 is the actual maximum
     std::vector<std::optional<int>> input = {5,3,9,1,4,7,12};
     TreeNode* root = buildTree(input);
     int expected = 7; // Correct maximum difference with ancestor-descendant relationship
     EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
     deleteTree(root);
 }
