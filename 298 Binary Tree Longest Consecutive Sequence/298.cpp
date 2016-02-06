/*

Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node 
to any node in the tree along the parent-child connections. 

The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,
            1
             \
              3
             / \
            2   4
                 \
                  5

Longest consecutive sequence path is 3-4-5, so return 3.

            2
             \
              3
             /
            2
           /
          1

Longest consecutive sequence path is 2-3,not 3-2-1, so return 2.

*/

#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// top-down
class Solution2 {
public:
    int longestConsecutive(TreeNode* root) {
        return helper(root, nullptr, 0);
    }
private:
    // length is of the path including the current node, but return value is not
    int helper(TreeNode* root, TreeNode* parent, int length) {
        if (!root) 
            return length;
        length = (parent && root->val == parent->val + 1) ? length + 1 : 1;
        return max(length, max(helper(root->left, root, length), helper(root->right, root, length)));
    }
};

// bottom-up
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        int longest = 0;
        dfs(root, longest);
        return longest;
    }
private:
    // return value is of the path including the current node
    int dfs(TreeNode* root, int& longest) {
        if (!root)
            return 0;

        int len = 1;
        int left = dfs(root->left, longest), right = dfs(root->right, longest);

        if (root->left && root->left->val == root->val + 1)
            len = 1 + left;

        if (root->right && root->right->val == root->val + 1)
            len = max(len, 1 + right);

        longest = max(longest, len);
        return len;
    }
};