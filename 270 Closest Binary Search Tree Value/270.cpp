/*

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

*/

#include <cmath>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// don't check if an int is equal to a double
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        while (root)
        {
            if (abs(root->val - target) < abs(closest - target))
                closest = root->val;
            if (target < root->val)
                root = root->left;
            else
                root = root->right;
        }
        return closest;
    }
};

// recursive
// closest is either the root's value (a) or the closest in the appropriate subtree (b)
class Solution2 {
public:
    int closestValue(TreeNode* root, double target) {
        int a = root->val;
        TreeNode *subtree = target < a ? root->left : root->right;
        if (!subtree)
            return a;
        int b = closestValue(subtree, target);
        return abs(a - target) < abs(b - target) ? a : b;
    }
};