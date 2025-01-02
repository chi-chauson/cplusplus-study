//
// Created by cchau on 12/29/2024.
//

#include "TreeUtil.h"
#include <algorithm>
#include <queue>
#include <stdexcept>

int TreeUtil::minDepth(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = minDepth(root->left);
    int rightDepth = minDepth(root->right);

    if (leftDepth == 0) {
        return 1 + rightDepth;
    } else if (rightDepth == 0) {
        return 1 + leftDepth;
    }

    return 1 + std::min(leftDepth, rightDepth);
}

void TreeUtil::dfs(TreeNode *node, int currentMin, int currentMax) {
    if (!node) return;

    // Update the max difference
    int potentialMaxDiff = std::max(std::abs(node->val - currentMin),
                                    std::abs(node->val - currentMax));
    maxDifference = std::max(maxDifference, potentialMaxDiff);

    // Update current min and max
    currentMin = std::min(currentMin, node->val);
    currentMax = std::max(currentMax, node->val);

    // Traverse left and right children
    dfs(node->left, currentMin, currentMax);
    dfs(node->right, currentMin, currentMax);
}

int TreeUtil::maxAncestorDiff(TreeNode *root) {
    if (!root) return 0;
    maxDifference = 0;
    dfs(root, root->val, root->val);
    return maxDifference;
}

int TreeUtil::depth(TreeNode *node) {
    if (node == nullptr) {
        return 0;
    }

    // Recursively compute the depth of left and right subtrees
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);

    // Update the maximum diameter if the path through this node is larger
    maxDiameter = std::max(maxDiameter, leftDepth + rightDepth);

    // Return the depth of the subtree rooted at this node
    return std::max(leftDepth, rightDepth) + 1;
}

int TreeUtil::diameterOfBinaryTree(TreeNode *root) {
    maxDiameter = 0;
    depth(root);
    return maxDiameter;
}

int TreeUtil::deepestLeavesSum(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }

    int sum = 0;
    std::queue<TreeNode*> queue;
    queue.push(root);

    // Perform BFS level by level
    while (!queue.empty()) {
        int levelSize = queue.size();
        sum = 0; // Reset sum for the current level

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = queue.front();
            queue.pop();
            sum += current->val;

            // Add child nodes for the next level
            if (current->left != nullptr) {
                queue.push(current->left);
            }
            if (current->right != nullptr) {
                queue.push(current->right);
            }
        }
    }

    // After the loop, sum contains the sum of the deepest leaves
    return sum;
}

std::vector<std::vector<int>> TreeUtil::zigzagLevelOrder(TreeNode *root) {
    std::vector<std::vector<int>> result;
    if (root == nullptr) {
        return result;
    }

    std::queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel;
        currentLevel.reserve(levelSize);

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* current = q.front();
            q.pop();
            currentLevel.push_back(current->val);

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }

        if (!leftToRight) {
            std::reverse(currentLevel.begin(), currentLevel.end());
        }

        result.push_back(currentLevel);
        leftToRight = !leftToRight;
    }

    return result;
}

int TreeUtil::findClosest(TreeNode *node, double target, int closest) {
    if (node == nullptr) {
        return closest;
    }

    // Update closest if current node is closer or equally close but smaller
    double currentDiff = std::abs(node->val - target);
    double closestDiff = std::abs(closest - target);
    if (currentDiff < closestDiff) {
        closest = node->val;
    } else if (currentDiff == closestDiff && node->val < closest) {
        closest = node->val;
    }

    // Decide whether to go left or right
    if (target < node->val) {
        return findClosest(node->left, target, closest);
    } else if (target > node->val) {
        return findClosest(node->right, target, closest);
    } else {
        // Exact match found
        return node->val;
    }
}

int TreeUtil::closestValue(TreeNode *root, double target) {
    if (root == nullptr) {
        throw std::invalid_argument("The BST root cannot be null.");
    }
    return findClosest(root, target, root->val);
}

TreeNode *TreeUtil::insertIntoBST(TreeNode *root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }

    TreeNode* current = root;
    while (true) {
        if (val < current->val) {
            if (current->left == nullptr) {
                current->left = new TreeNode(val);
                break;
            }
            current = current->left;
        } else { // val > current->val since values are unique
            if (current->right == nullptr) {
                current->right = new TreeNode(val);
                break;
            }
            current = current->right;
        }
    }
    return root;
}
