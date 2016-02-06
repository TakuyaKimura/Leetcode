/*

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree
in which the depth of the two subtrees of every node never differ by more than 1.

*/

#include <algorithm>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// dfs
// check balance and return height at the same time, so faster
class Solution2 {
public:
    bool isBalanced(TreeNode *root) {
        return dfsDepth(root) != -1;
    }

private:
    int dfsDepth(TreeNode *root) {
        if (!root)
            return 0;
        int left = dfsDepth(root->left);
        if (left == -1)
            return -1;
        int right = dfsDepth(root->right);
        if (right == -1)
            return -1;
        if (abs(left - right) > 1)
            return -1;
        return 1 + max(left, right);
    }
};

// dfs, but have to do another dfs for each node to find the height
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        return !root || isBalanced(root->left) && isBalanced(root->right) && abs(depth(root->left) - depth(root->right)) < 2;
    }

private:
    int depth(TreeNode *root) {
        if (!root)
            return 0;
        return 1 + max(depth(root->left), depth(root->right));
    }
};