//
// Created by cchau on 12/29/2024.
//

#include "TreeUtil.h"
#include <algorithm>

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
