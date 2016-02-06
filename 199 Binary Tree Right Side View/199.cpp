/*

Given a binary tree, imagine yourself standing on the right side of it, 
return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,

       1            <---
     /   \
    2     3         <---
     \     \
      5     4       <---

You should return [1, 3, 4].

*/

#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// DFS
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        dfs(root, 1, result);  // or 0
        return result;
    }
private:
    void dfs(TreeNode* root, int level, vector<int>& result) {
        if (!root)
            return;
        if (level > result.size())  // or ==
            result.push_back(root->val);
        dfs(root->right, level + 1, result);
        dfs(root->left, level + 1, result);
    }
};

// divide and conquer
class Solution2 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root)
            return result;
        result.push_back(root->val);  // don't forget
        vector<int> leftVec = rightSideView(root->left), rightVec = rightSideView(root->right);
        int left = leftVec.size(), right = rightVec.size();
        int max = left > right ? left : right;  // or result.resize(max+1); result[i+1] = leftVec[i] or rightVec[i]
        for (int i = 0; i < max; ++i)
            if (i >= right)
                result.push_back(leftVec[i]);
            else
                result.push_back(rightVec[i]);
        return result;
    }
};

// iterative
class Solution3 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        queue<TreeNode*> q;
        TreeNode *node;
        int size;
        if (root)
            q.push(root);
        while (!q.empty())
        {
            size = q.size();
            while (size--)
            {
                node = q.front();
                q.pop();
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            result.push_back(node->val);  // the last one on the level
        }
        return result;
    }
};