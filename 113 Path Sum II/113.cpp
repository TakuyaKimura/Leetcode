/*

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return
    [
        [5,4,11,2],
        [5,8,4,5]
    ]

*/

#include <vector>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> path;
        if (root)
            dfs(root, sum, result, path);
        return result;
    }
private:
    void dfs(TreeNode* root, int sum, vector<vector<int>>& result, vector<int>& path) {
        path.push_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right && sum == 0)
            result.push_back(path);
        if (root->left)
            dfs(root->left, sum, result, path);
        if (root->right)
            dfs(root->right, sum, result, path);
        path.pop_back();
    }
};

// only difference is when to check for null
class Solution2 {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(root, sum, result, path);
        return result;
    }
private:
    void dfs(TreeNode* root, int sum, vector<vector<int>>& result, vector<int>& path) {
        if (!root)
            return;
        path.push_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right && sum == 0)
            result.push_back(path);
        dfs(root->left, sum, result, path);
        dfs(root->right, sum, result, path);
        path.pop_back();
    }
};