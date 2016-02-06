/*

Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

         3
        / \
       9  20
         /  \
        15   7

return its bottom-up level order traversal as:
    [
        [15,7],
        [9,20],
        [3]
    ]

*/

#include <vector>
#include <deque>
#include <queue>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// bfs using one queue
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        TreeNode *node;
        queue<TreeNode*> q;
        int size, i;
        if (root)
            q.push(root);
        while (!q.empty())
        {
            size = q.size();
            result.push_back(vector<int>());
            for (i = 0; i < size; ++i)
            {
                node = q.front();
                q.pop();
                result.back().push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// dfs
class Solution2 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        if (!root)
            return result;
        dfs(root, 0);
        reverse(result.begin(), result.end());
        return result;
    }
private:
    vector<vector<int>> result;
    void dfs(TreeNode *root, int level) {
        if (level == result.size())
            result.push_back(vector<int>());  // syntax: vector<int>()
        result[level].push_back(root->val);
        if (root->left)
            dfs(root->left, level + 1);
        if (root->right)
            dfs(root->right, level + 1);
    }
};

// Can use bfs and two queues to store nodes of current level and next level, respectively
// then switch names
class Solution3 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        vector<vector<int>> result;
        if (!root)
            return result;
        TreeNode *nd;
        vector<int> wholeLevel;
        deque<TreeNode*> current, next;
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
        reverse(result.begin(), result.end());
        return result;
    }
};

class Solution4 {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        if (!root)
            return result;
        TreeNode *node;
        deque<TreeNode*> stk;
        stk.push_back(root);
        stk.push_back(nullptr);
        for (int i = 0; i < stk.size() - 1; ++i)  // last is null, don't need to consider; otherwise, infinite loop
        {
            node = stk[i];
            if (node)
            {
                if (node->right)
                    stk.push_back(node->right);
                if (node->left)
                        stk.push_back(node->left);
            }
            else
                stk.push_back(nullptr);
        }
        for (auto node : stk)
        {
            if (!node)
                result.push_back(vector<int>());
            else
                result.back().push_back(node->val);
        }
        return result;
    }
};