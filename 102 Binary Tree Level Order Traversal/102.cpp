/*

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
         3
        / \
       9  20
         /  \
        15   7

return its level order traversal as:
    [
        [3],
        [9,20],
        [15,7]
    ]

*/

#include <vector>
#include <queue>
#include <deque>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// dfs, nodes are added as preorder
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        if (root)
            dfs(root, 0, result);
        return result;
    }
private:
    void dfs(TreeNode *root, int level, vector<vector<int>>& result) {
        if (level == result.size())
            result.push_back(vector<int>());  // syntax: vector<int>()
        result[level].push_back(root->val);
        if (root->left)
            dfs(root->left, level + 1, result);
        if (root->right)
            dfs(root->right, level + 1, result);
    }
};

// bfs
class Solution2 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        if (root)
            q.push(root);
        int size, i;
        TreeNode *node;
        while (!q.empty())
        {
            size = q.size();
            result.push_back(vector<int>(size));
            for (i = 0; i < size; ++i)
            {
                node = q.front();
                q.pop();
                result.back()[i] = node->val;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return result;
    }
};

// Can use bfs and two queues to store nodes of current level and next level, respectively
// then switch names
class Solution3 {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        if (!root)
            return result;
        TreeNode *nd;
        vector<int> wholeLevel;
        deque<TreeNode *> current;
        deque<TreeNode *> next;
        current.push_back(root);
        while (!current.empty())
        {
            nd = current.front();
            current.pop_front();
            wholeLevel.push_back(nd->val);

            if (nd->left)
                next.push_back(nd->left);
            if (nd->right)
                next.push_back(nd->right);
            if (current.empty())
            {
                current = next;
                next.clear();
                result.push_back(wholeLevel);
                wholeLevel.clear();
            }
        }
        return result;
    }
};