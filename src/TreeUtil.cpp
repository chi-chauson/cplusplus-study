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
