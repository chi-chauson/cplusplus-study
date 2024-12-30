//
// Created by cchau on 12/29/2024.
//

#ifndef PLAYGROUND_TREEUTIL_H
#define PLAYGROUND_TREEUTIL_H


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
    void dfs(TreeNode* node, int currentMin, int currentMax);
public:
    int minDepth(TreeNode* root);
    int maxAncestorDiff(TreeNode* root);

};


#endif //PLAYGROUND_TREEUTIL_H
