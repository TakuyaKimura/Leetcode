/*

Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,

                  5
                 / \
                4   8
               /   / \
              11  13  4
             /  \      \
            7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

*/

#include <stack>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursive
class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root)
            return false;

        if (!root->left && !root->right)
            return sum == root->val;

        // not a leaf
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

// iterative
class Solution2 {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        stack<pair<TreeNode*, int>> stk;
        if (root)
            stk.push(make_pair(root, sum));
        while (!stk.empty())
        {
            root = stk.top().first;
            sum = stk.top().second;
            stk.pop();
            if (!root->left && !root->right && root->val == sum)
                return true;
            if (root->right)
                stk.push(make_pair(root->right, sum - root->val));
            if (root->left)
                stk.push(make_pair(root->left, sum - root->val));
        }
        return false;
    }
};