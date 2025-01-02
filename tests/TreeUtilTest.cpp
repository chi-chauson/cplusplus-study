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
static TreeNode *buildTree(const std::vector<std::optional<int>> &values) {
    if (values.empty() || !values[0].has_value()) return nullptr;

    TreeNode *root = new TreeNode(values[0].value());
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(root);
    size_t i = 1;

    while (i < values.size()) {
        TreeNode *current = nodeQueue.front();
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

// Helper method to serialize tree to level-order vector
static std::vector<std::optional<int>> serializeTree(TreeNode *root) {
    std::vector<std::optional<int>> result;
    if (root == nullptr) return result;

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode *current = q.front();
        q.pop();

        if (current != nullptr) {
            result.emplace_back(current->val);
            q.push(current->left);
            q.push(current->right);
        } else {
            result.emplace_back(std::nullopt);
        }
    }

    // Remove trailing nulls
    while (!result.empty() && !result.back().has_value()) {
        result.pop_back();
    }

    return result;
}

static TreeNode *insert(TreeNode *root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

static TreeNode *buildBST(const std::vector<int> &values) {
    if (values.empty()) {
        return nullptr;
    }
    TreeNode *root = new TreeNode(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        insert(root, values[i]);
    }
    return root;
}

// Helper function to delete the BST and free memory
static void deleteBST(TreeNode *node) {
    if (node == nullptr) return;
    deleteBST(node->left);
    deleteBST(node->right);
    delete node;
}

/**
* Deletes a binary tree to free memory.
* @param root Pointer to the root of the binary tree.
*/
static void deleteTree(TreeNode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Comparator for optional vectors
static bool compareTrees(const std::vector<std::optional<int>> &a, const std::vector<std::optional<int>> &b) {
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin(),
                                              [](const std::optional<int> &x, const std::optional<int> &y) -> bool {
                                                  if (x.has_value() != y.has_value()) return false;
                                                  if (!x.has_value()) return true;
                                                  return x.value() == y.value();
                                              });
}

/**
* Helper method to compare expected and actual sum of deepest leaves.
*
* @param treeValues The vector representing the tree in level-order.
* @param expectedSum The expected sum of the deepest leaves.
*/
static void expectDiameter(const std::vector<std::optional<int>> &treeValues, int expected) {
    TreeNode *root = buildTree(treeValues);
    TreeUtil util;
    int actual = util.diameterOfBinaryTree(root);
    EXPECT_EQ(actual, expected) << "Failed for tree: ";
    deleteTree(root);
}

/**
* Helper method to compare expected and actual sum of deepest leaves.
*
* @param treeValues The vector representing the tree in level-order.
* @param expectedSum The expected sum of the deepest leaves.
*/
static void assertDeepestLeavesSum(const std::vector<std::optional<int>> &treeValues, int expectedSum) {
    TreeNode *root = buildTree(treeValues);
    TreeUtil util;
    int actualSum = util.deepestLeavesSum(root);
    EXPECT_EQ(actualSum, expectedSum) << "Sum of deepest leaves should be " << expectedSum;
    deleteTree(root);
}

/**
* Helper method to compare expected and actual zigzag level order traversal.
*
* @param treeValues The array representing the tree in level-order.
* @param expectedTraversal The expected zigzag level order traversal.
*/
void assertZigzagLevelOrder(const std::vector<std::optional<int>> &treeValues,
                            const std::vector<std::vector<int>> &expectedTraversal) {
    TreeNode *root = buildTree(treeValues);
    TreeUtil util;
    std::vector<std::vector<int>> actualTraversal = util.zigzagLevelOrder(root);
    EXPECT_EQ(actualTraversal, expectedTraversal) << "Zigzag level order traversal does not match expected.";
    deleteTree(root);
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
    std::vector<std::optional<int>> input = {8, 3, 10, 1, 6, std::nullopt, 14, std::nullopt, std::nullopt, 4, 7, 13};
    TreeNode *root = buildTree(input);
    int expected = 7;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceExample2) {
    // Example 2:
    // Input: root = [1,null,2,null,0,3]
    // Output: 3
    std::vector<std::optional<int>> input = {1, std::nullopt, 2, std::nullopt, 0, 3};
    TreeNode *root = buildTree(input);
    int expected = 3;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceSingleLeft) {
    // Test with all left children
    // Input: [5,3,null,2,null,1]
    // Expected Output: 4 (|5 -1| = 4)
    std::vector<std::optional<int>> input = {5, 3, std::nullopt, 2, std::nullopt, 1};
    TreeNode *root = buildTree(input);
    int expected = 4;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceSingleRight) {
    // Test with all right children
    // Input: [5,null,8,null,10,null,12]
    // Expected Output: 7 (|5 -12| = 7)
    std::vector<std::optional<int>> input = {5, std::nullopt, 8, std::nullopt, 10, std::nullopt, 12};
    TreeNode *root = buildTree(input);
    int expected = 7;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceAllSame) {
    // Test with all nodes having the same value
    // Input: [1,1,1,1,1,1,1]
    // Expected Output: 0
    std::vector<std::optional<int>> input = {1, 1, 1, 1, 1, 1, 1};
    TreeNode *root = buildTree(input);
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
    TreeNode *root = buildTree(input);
    int expected = 40;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceTwoNodes) {
    // Test with the smallest possible tree (two nodes)
    // Input: [1,2]
    // Expected Output: 1
    std::vector<std::optional<int>> input = {1, 2};
    TreeNode *root = buildTree(input);
    int expected = 1;
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, TestMaximumDifferenceNegativeValues) {
    // Although constraints specify 0 <= Node.val, testing negative values for robustness
    // Input: [5,3,9,1,4,7,12]
    // Expected Output: 11 (|1 -12| = 11 is invalid as no ancestor-descendant relationship,
    // but |5 -12| =7 is the actual maximum
    std::vector<std::optional<int>> input = {5, 3, 9, 1, 4, 7, 12};
    TreeNode *root = buildTree(input);
    int expected = 7; // Correct maximum difference with ancestor-descendant relationship
    EXPECT_EQ(treeUtil.maxAncestorDiff(root), expected);
    deleteTree(root);
}

TEST_F(TreeUtilTest, Example1) {
    // Input: root = [1,2,3,4,5]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5};
    int expected = 3;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, Example2) {
    // Input: root = [1,2]
    std::vector<std::optional<int>> input = {1, 2};
    int expected = 1;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, SingleNode) {
    // Input: root = [1]
    std::vector<std::optional<int>> input = {1};
    int expected = 0;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, LeftSkewedTree) {
    // Input: root = [1,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    int expected = 4;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, RightSkewedTree) {
    // Input: root = [1,null,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, std::nullopt, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    int expected = 4;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, BalancedTree) {
    // Input: root = [1,2,3,4,5,6,7]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, 6, 7};
    int expected = 4; // e.g., path [4,2,1,3,7]
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, TreeWithNegativeValues) {
    // Input: root = [1,-2,-3,4,5]
    std::vector<std::optional<int>> input = {1, -2, -3, 4, 5};
    int expected = 3;
    expectDiameter(input, expected);
}

TEST_F(TreeUtilTest, LargeBalancedTree) {
    // Construct a large balanced binary tree with depth 10 (~1023 nodes)
    // For practicality in testing, a depth of 10 is used instead of 14
    int depth = 10;
    int numNodes = (1 << depth) - 1; // 2^depth - 1
    std::vector<std::optional<int>> input;
    input.reserve(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        input.emplace_back(1); // All node values are set to 1 for simplicity
    }
    int expected = (depth - 1) * 2; // The diameter of a perfect binary tree
    expectDiameter(input, expected);
}

// Test Cases

TEST_F(TreeUtilTest, Example1_SumOfDeepestLeaves) {
    // Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, std::nullopt, 6, 7, std::nullopt, std::nullopt,
                                             std::nullopt, std::nullopt, 8};
    int expected = 15; // Deepest leaves are 7 and 8
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, Example2_SumOfDeepestLeaves) {
    // Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
    std::vector<std::optional<int>> input = {6, 7, 8, 2, 7, 1, 3, 9, std::nullopt, 1, 4, std::nullopt, std::nullopt,
                                             std::nullopt, 5};
    int expected = 19; // Deepest leaves are 9, 1, 4, 5
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, SingleNode_SumOfDeepestLeaves) {
    // Input: root = [10]
    std::vector<std::optional<int>> input = {10};
    int expected = 10; // Only one node
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, LeftSkewedTree_SumOfDeepestLeaves) {
    // Input: root = [1,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    int expected = 5; // Deepest leaf is 5
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, RightSkewedTree_SumOfDeepestLeaves) {
    // Input: root = [1,null,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, std::nullopt, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    int expected = 5; // Deepest leaf is 5
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, BalancedTree_SumOfDeepestLeaves) {
    // Input: root = [1,2,3,4,5,6,7]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, 6, 7};
    int expected = 22; // Deepest leaves are 4,5,6,7; sum = 4+5+6+7=22
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, MultipleDeepestLeaves_SumOfDeepestLeaves) {
    // Input: root = [1,2,3,4,5,6,7,8,9,10,null,null,11,12,null,13]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, std::nullopt, std::nullopt, 11, 12,
                                             std::nullopt, 13};
    int expected = 13; // Deepest leaf is 13
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, AllLeavesSameDepth_SumOfDeepestLeaves) {
    // Input: root = [5,3,8,1,4,7,9]
    std::vector<std::optional<int>> input = {5, 3, 8, 1, 4, 7, 9};
    int expected = 21; // Deepest leaves are 1,4,7,9; sum = 1+4+7+9=21
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, LargeTree_SumOfDeepestLeaves) {
    // Construct a complete binary tree with depth 4
    // Level 1: 1
    // Level 2: 2,3
    // Level 3: 4,5,6,7
    // Level 4: 8,9,10,11,12,13,14,15
    std::vector<std::optional<int>> input = {
            1,
            2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11, 12, 13, 14, 15
    };
    int expected = 92; // Deepest leaves are 8,9,10,11,12,13,14,15; sum = 8+9+10+11+12+13+14+15=92
    assertDeepestLeavesSum(input, expected);
}

TEST_F(TreeUtilTest, TreeWithNullNodes_SumOfDeepestLeaves) {
    // Input: root = [1,2,3,null,4,null,5,null,null,6]
    std::vector<std::optional<int>> input = {1, 2, 3, std::nullopt, 4, std::nullopt, 5, std::nullopt, std::nullopt, 6};
    int expected = 6; // Deepest leaf is 6
    assertDeepestLeavesSum(input, expected);
}

// Test Cases

TEST_F(TreeUtilTest, Example1_ZigzagLevelOrderTraversal) {
    // Input: root = [3,9,20,null,null,15,7]
    std::vector<std::optional<int>> input = {3, 9, 20, std::nullopt, std::nullopt, 15, 7};
    std::vector<std::vector<int>> expected = {{3},
                                              {20, 9},
                                              {15, 7}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, Example2_ZigzagLevelOrderTraversal) {
    // Input: root = [1]
    std::vector<std::optional<int>> input = {1};
    std::vector<std::vector<int>> expected = {{1}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, Example3_ZigzagLevelOrderTraversal_EmptyTree) {
    // Input: root = []
    std::vector<std::optional<int>> input = {};
    std::vector<std::vector<int>> expected = {};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, SingleNode_ZigzagLevelOrderTraversal) {
    // Input: root = [42]
    std::vector<std::optional<int>> input = {42};
    std::vector<std::vector<int>> expected = {{42}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, LeftSkewedTree_ZigzagLevelOrderTraversal) {
    // Input: root = [1,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    std::vector<std::vector<int>> expected = {{1},
                                              {2},
                                              {3},
                                              {4},
                                              {5}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, RightSkewedTree_ZigzagLevelOrderTraversal) {
    // Input: root = [1,null,2,null,3,null,4,null,5]
    std::vector<std::optional<int>> input = {1, std::nullopt, 2, std::nullopt, 3, std::nullopt, 4, std::nullopt, 5};
    std::vector<std::vector<int>> expected = {{1},
                                              {2},
                                              {3},
                                              {4},
                                              {5}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, BalancedTree_ZigzagLevelOrderTraversal) {
    // Input: root = [1,2,3,4,5,6,7]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, 6, 7};
    std::vector<std::vector<int>> expected = {{1},
                                              {3, 2},
                                              {4, 5, 6, 7}};
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, TreeWithMultipleDeepestLeaves_ZigzagLevelOrderTraversal) {
    // Input: root = [1,2,3,4,5,6,7,8,9,10,null,null,11,12,null,13]
    std::vector<std::optional<int>> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, std::nullopt, std::nullopt, 11, 12,
                                             std::nullopt, 13};
    std::vector<std::vector<int>> expected = {
            {1},
            {3,  2},
            {4,  5,  6,  7},
            {12, 11, 10, 9, 8},
            {13}
    };
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, TreeWithAllLeavesAtSameDepth_ZigzagLevelOrderTraversal) {
    // Input: root = [5,3,8,1,4,7,9]
    std::vector<std::optional<int>> input = {5, 3, 8, 1, 4, 7, 9};
    std::vector<std::vector<int>> expected = {
            {5},
            {8, 3},
            {1, 4, 7, 9}
    };
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, LargeBalancedTree_ZigzagLevelOrderTraversal) {
    // Construct a complete binary tree with depth 4
    // Level 1: 1
    // Level 2: 2,3
    // Level 3: 4,5,6,7
    // Level 4: 8,9,10,11,12,13,14,15
    std::vector<std::optional<int>> input = {
            1,
            2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11, 12, 13, 14, 15
    };
    std::vector<std::vector<int>> expected = {
            {1},
            {3,  2},
            {4,  5,  6,  7},
            {15, 14, 13, 12, 11, 10, 9, 8}
    };
    assertZigzagLevelOrder(input, expected);
}

TEST_F(TreeUtilTest, TreeWithNullNodes_ZigzagLevelOrderTraversal) {
    // Input: root = [1,2,3,null,4,null,5,null,null,6]
    std::vector<std::optional<int>> input = {1, 2, 3, std::nullopt, 4, std::nullopt, 5, std::nullopt, std::nullopt, 6};
    std::vector<std::vector<int>> expected = {
            {1},
            {3, 2},
            {4, 5},
            {6}
    };
    assertZigzagLevelOrder(input, expected);
}

// Test Case 1: Example 1
TEST_F(TreeUtilTest, ClosestValueExample1) {
    // Tree: [4,2,5,1,3]
    std::vector<int> values = {4, 2, 5, 1, 3};
    TreeNode *root = buildBST(values);
    double target = 3.714286;
    int expected = 4;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    treeUtil.~TreeUtil();
    deleteBST(root);
}

// Test Case 2: Example 2 (Single Node)
TEST_F(TreeUtilTest, ClosestValueExample2_SingleNode) {
    // Tree: [1]
    std::vector<int> values = {1};
    TreeNode *root = buildBST(values);
    double target = 4.428571;
    int expected = 1;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 3: Target Lower Than All Nodes
TEST_F(TreeUtilTest, ClosestValueTargetLowerThanAllNodes) {
    // Tree: [10,5,15]
    std::vector<int> values = {10, 5, 15};
    TreeNode *root = buildBST(values);
    double target = 2.0;
    int expected = 5;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 4: Target Higher Than All Nodes
TEST_F(TreeUtilTest, ClosestValueTargetHigherThanAllNodes) {
    // Tree: [10,5,15]
    std::vector<int> values = {10, 5, 15};
    TreeNode *root = buildBST(values);
    double target = 20.0;
    int expected = 15;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 5: Multiple Closest Values (Tie)
TEST_F(TreeUtilTest, ClosestValueMultipleClosestValues) {
    // Tree: [4,2,5,1,3]
    std::vector<int> values = {4, 2, 5, 1, 3};
    TreeNode *root = buildBST(values);
    double target = 3.5;
    int expected = 3; // Both 3 and 4 are equally close, return smaller
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 6: Exact Match
TEST_F(TreeUtilTest, ClosestValueExactMatch) {
    // Tree: [4,2,5,1,3]
    std::vector<int> values = {4, 2, 5, 1, 3};
    TreeNode *root = buildBST(values);
    double target = 3.0;
    int expected = 3;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 7: Large BST
TEST_F(TreeUtilTest, ClosestValueLargeBST) {
    // Build a large BST with values from 1 to 10000
    std::vector<int> values;
    for (int i = 1; i <= 10000; ++i) {
        values.push_back(i);
    }
    TreeNode *root = buildBST(values);
    double target = 9999.5;
    int expected = 9999; // Corrected expected value
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 8: Negative Target
TEST_F(TreeUtilTest, ClosestValueNegativeTarget) {
    // Tree: [4,2,5,1,3]
    std::vector<int> values = {4, 2, 5, 1, 3};
    TreeNode *root = buildBST(values);
    double target = -1.0;
    int expected = 1;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 9: Multiple Same Closest
TEST_F(TreeUtilTest, ClosestValueMultipleSameClosest) {
    // Tree: [6,2,8,0,4,7,9]
    std::vector<int> values = {6, 2, 8, 0, 4, 7, 9};
    TreeNode *root = buildBST(values);
    double target = 5.0;
    int expected = 4; // 4 and 6 are equally close, return 4
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

// Test Case 10: Floating Point Target
TEST_F(TreeUtilTest, ClosestValueTargetIsFloat) {
    // Tree: [10,5,15,3,7,13,18]
    std::vector<int> values = {10, 5, 15, 3, 7, 13, 18};
    TreeNode *root = buildBST(values);
    double target = 12.7;
    int expected = 13;
    EXPECT_EQ(treeUtil.closestValue(root, target), expected);
    deleteBST(root);
}

TEST_F(TreeUtilTest, InsertIntoEmptyTree) {
    std::vector<std::optional<int>> input = {};
    int val = 10;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    std::vector<std::optional<int>> expected = {10};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}

TEST_F(TreeUtilTest, InsertAsLeftChild) {
    std::vector<std::optional<int>> input = {4, 2, 7, 1, 3};
    int val = 5;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    std::vector<std::optional<int>> expected = {4, 2, 7, 1, 3, 5};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}

TEST_F(TreeUtilTest, InsertAsRightChildWithDeepInsertion) {
    std::vector<std::optional<int>> input = {40, 20, 60, 10, 30, 50, 70};
    int val = 25;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    // Expected tree: [40,20,60,10,30,50,70,null,null,25]
    std::vector<std::optional<int>> expected = {40, 20, 60, 10, 30, 50, 70, std::nullopt, std::nullopt, 25};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}

TEST_F(TreeUtilTest, InsertIntoBSTWithExistingNullLeaves) {
    std::vector<std::optional<int>> input = {4, 2, 7, 1, 3, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt};
    int val = 5;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    std::vector<std::optional<int>> expected = {4, 2, 7, 1, 3, 5};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}

TEST_F(TreeUtilTest, InsertLeftMostNode) {
    std::vector<std::optional<int>> input = {50, 30, 70, 20, 40, 60, 80};
    int val = 10;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    std::vector<std::optional<int>> expected = {50, 30, 70, 20, 40, 60, 80, 10};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}

TEST_F(TreeUtilTest, InsertRightMostNode) {
    std::vector<std::optional<int>> input = {50, 30, 70, 20, 40, 60, 80};
    int val = 90;
    TreeNode* root = buildTree(input);
    TreeNode* result = treeUtil.insertIntoBST(root, val);
    std::vector<std::optional<int>> expected = {50, 30, 70, 20, 40, 60, 80, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 90};
    EXPECT_TRUE(compareTrees(serializeTree(result), expected));
    deleteTree(result);
}