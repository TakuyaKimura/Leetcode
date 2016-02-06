/*

Given a binary tree, return the zigzag level order traversal of its nodes' values. 
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
         3
        / \
       9  20
         /  \
        15   7

return its zigzag level order traversal as:
    [
        [3],
        [20,9],
        [15,7]
    ]

*/

#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// use two stacks
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        vector<int> newLevel;
        TreeNode *node;
        stack<TreeNode*> s1, s2;
        if (root)
            s1.push(root);

        while (!s1.empty())  // don't need to check s2 here -- because we've just checked it at the end of last loop
        {
            while (!s1.empty())  // for levels to be traversed from left to right
            {
                node = s1.top();
                s1.pop();
                newLevel.push_back(node->val);
                if (node->left)  // left first
                    s2.push(node->left);
                if (node->right)
                    s2.push(node->right);
            }
            result.push_back(newLevel);
            newLevel.clear();

            while (!s2.empty())  // for levels to be traversed from right to left
            {
                node = s2.top();
                s2.pop();
                newLevel.push_back(node->val);
                if (node->right) // right first!!!
                    s1.push(node->right);
                if (node->left)
                    s1.push(node->left);
            }
            if (!newLevel.empty())
            {
                result.push_back(newLevel);
                newLevel.clear();
            }
        }
        return result;
    }
};

// use one queue
class Solution2 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root)
            return result;

        TreeNode *node;
        queue<TreeNode *> q;
        q.push(root);
        int currNum = 1, nextNum = 0;
        bool leftToRight = true;
        while (currNum)
        {
            vector<int> newLevel;
            while (currNum)
            {
                node = q.front();
                q.pop();
                --currNum;
                if (leftToRight)
                    newLevel.push_back(node->val);
                else
                    newLevel.insert(newLevel.begin(), node->val);  // push to the front
                if (node->left)
                {
                    q.push(node->left);
                    ++nextNum;
                }
                if (node->right)
                {
                    q.push(node->right);
                    ++nextNum;
                }
            }
            result.push_back(newLevel);
            leftToRight = !leftToRight;
            currNum = nextNum;
            nextNum = 0;
        }
        return result;
    }
};

// use one queue, like this one over Solution2
class Solution3 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int n, i, idx;
        bool leftToRight = true;
        TreeNode *node;
        queue<TreeNode*> q;
        if (root)
            q.push(root);
        while (!q.empty())
        {
            n = q.size();
            vector<int> newLevel(n);
            for (i = 0; i < n; ++i)
            {
                node = q.front();
                q.pop();
                idx = leftToRight ? i : n - 1 - i;  //calculate the index instead of pushing or inserting
                newLevel[idx] = node->val;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            result.push_back(newLevel);
            leftToRight = !leftToRight;
        }
        return result;
    }
};

// DFS, recursion
// for each level, need to traverse all the levels above it, a lot of redundant work
class Solution4 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        TreeNode *node;
        bool leftToRight = true;
        int height = getHeight(root);
        for (int i = 0; i < height; ++i)
        {
            vector<int> newLevel;
            traverse(newLevel, root, i, leftToRight);
            result.push_back(newLevel);
            leftToRight = !leftToRight;
        }
        return result;
    }
private:
    int getHeight(TreeNode *root) {
        if (!root)
            return 0;
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }
    void traverse(vector<int>& newLevel, TreeNode* root, int level, bool leftToRight) {
        if (!root)
            return;
        if (level == 0)
        {
            newLevel.push_back(root->val);
            return;
        }
        if (leftToRight)
        {
            // don't reverse the direction here!!!
            // it's determined from the top level
            // i.e. if level 5 is gonna be traversed from right to left
            // then level 0-5 will all be traversed from right to left
            traverse(newLevel, root->left, level - 1, leftToRight);  // left first
            traverse(newLevel, root->right, level - 1, leftToRight);
        }
        else
        {
            traverse(newLevel, root->right, level - 1, leftToRight); // right first
            traverse(newLevel, root->left, level - 1, leftToRight);
        }
    }
};