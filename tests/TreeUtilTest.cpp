//
// Created by cchau on 12/29/2024.
//
#include "TreeUtil.h"
#include "gtest/gtest.h"

class TreeUtilTest : public ::testing::Test {
protected:
    TreeUtil treeUtil;
};

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
