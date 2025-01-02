//
// Created by cchau on 12/29/2024.
//

#ifndef PLAYGROUND_TREEUTIL_H
#define PLAYGROUND_TREEUTIL_H

#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class TreeUtil {
private:
    int maxDifference;
    int maxDiameter;
    void dfs(TreeNode* node, int currentMin, int currentMax);
    int depth(TreeNode* node);
    int findClosest(TreeNode* node, double target, int closest);
public:
    int minDepth(TreeNode* root);
    int maxAncestorDiff(TreeNode* root);
    int diameterOfBinaryTree(TreeNode* root);
    int deepestLeavesSum(TreeNode* root);
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root);
    int closestValue(TreeNode* root, double target);
    TreeNode* insertIntoBST(TreeNode* root, int val);
};


#endif //PLAYGROUND_TREEUTIL_H
