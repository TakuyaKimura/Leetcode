/*

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

*/

#include <algorithm>
#include <queue>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// dfs, recursively
// need to traverse all nodes
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
            return 0;
        int minD = INT_MAX, depth = 1;
        dfs(root, depth, minD);
        return minD;
    }
private:
    void dfs(TreeNode* root, int depth, int& minD) {
        if (!root->left && !root->right && depth < minD)
            minD = depth;
        if (root->left)
            dfs(root->left, depth + 1, minD);
        if (root->right)
            dfs(root->right, depth + 1, minD);
    }
};

// divide-and-conquer
class Solution2 {
public:
    int minDepth(TreeNode *root) {
        if (!root)
            return 0;
        if (!root->left)
            return 1 + minDepth(root->right);  // note not take the min
        if (!root->right)
            return 1 + minDepth(root->left);   // note not take the min
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

// bfs, iteratively
// return whenever encounter a leaf node
// don't need to traverse all nodes
class Solution3 {
public:
    int minDepth(TreeNode *root) {
        if (!root)
            return 0;
        int depth = 1, size;
        queue<TreeNode*> q;
        TreeNode *node;
        q.push(root);
        while (true)
        {
            size = q.size();
            while (size--)
            {
                node = q.front();
                q.pop();
                if (!node->left && !node->right)  // leaf node, found the min
                    return depth;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            ++depth;
        }
    }
};