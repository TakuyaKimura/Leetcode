/*

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Just search from root to bottom, trying to find the smallest node larger than p 
// and return the last one that was larger (whenever make a left turn, remember that node)

// Just like searching for a value, but when we found equal we go to right
// O(height)
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode *candidate = nullptr;
        while (root)
            root = (root->val > p->val) ? (candidate = root)->left : root->right;
        return candidate;
    }
};

// recursive
class Solution2 {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root)
            return nullptr;

        if (root->val <= p->val)
            return inorderSuccessor(root->right, p);

        TreeNode *left = inorderSuccessor(root->left, p);
        return left ? left : root;
    }
};