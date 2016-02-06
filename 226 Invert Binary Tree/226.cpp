/*

Invert a binary tree.

             4
           /   \
          2     7
         / \   / \
        1   3 6   9

to

             4
           /   \
          7     2
         / \   / \
        9   6 3   1


Trivia:
This problem was inspired by this original tweet by Max Howell:
    Google: 90% of our engineers use the software you wrote (Homebrew), 
    but you can¡¯t invert a binary tree on a whiteboard so fuck off.
    https://twitter.com/mxcl/status/608682016205344768

*/

#include <deque>
#include <stack>
#include <queue>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root)
        {
            TreeNode *temp = root->left;
            root->left = invertTree(root->right);
            root->right = invertTree(temp);
        }
        return root;
    }
};

class Solution2 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root)
        {
            root->left = invertTree(root->left);
            root->right = invertTree(root->right);
            swap(root->left, root->right);
        }
        return root;
    }
};

class Solution3 {
public:
    TreeNode* invertTree(TreeNode* root) {
        deque<TreeNode*> d;
        TreeNode *node;
        d.push_back(root);
        while (!d.empty())
        {
            node = d.back();
            d.pop_back();
            if (node)
            {
                swap(node->left, node->right);
                d.push_back(node->left);
                d.push_back(node->right);
            }
        }
        return root;
    }
};

// DFS
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        TreeNode *node;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty())
        {
            node = s.top();
            s.pop();
            if (node)
            {
                swap(node->left, node->right);
                s.push(node->left);
                s.push(node->right);
            }
        }
        return root;
    }
};

// BFS
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        TreeNode *node;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            node = q.front();
            q.pop();
            if (node)
            {
                swap(node->left, node->right);
                q.push(node->left);
                q.push(node->right);
            }
        }
        return root;
    }
};