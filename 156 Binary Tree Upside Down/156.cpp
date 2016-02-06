/*

Given a binary tree where all the right nodes are either leaf nodes with a sibling
(a left node that shares the same parent node) or empty, 

flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. 

Return the new root.

For example:
Given a binary tree {1,2,3,4,5},

        1
       / \
      2   3
     / \
    4   5

return the root of the binary tree [4,5,2,#,#,3,1].

        4
       / \
      5   2
         / \
        3   1

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursive
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left)
            return root;
        TreeNode *curLeft = root->left, *curRight = root->right;
        TreeNode *newRoot = upsideDownBinaryTree(curLeft);
        curLeft->left = curRight;
        curLeft->right = root;
        root->left = root->right = nullptr;
        return newRoot;
    }
};

// iterative
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        TreeNode *curLeft = nullptr, *curRight = nullptr, *nextLeft, *nextRight;
        while (root)
        {
            nextLeft = root->left;
            nextRight = root->right;
            root->left = curLeft;
            root->right = curRight;
            curRight = root;
            root = nextLeft;
            curLeft = nextRight;
        }
        return curRight;
    }
};