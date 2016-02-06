/*

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

    The left subtree of a node contains only nodes with keys less than the node's key.

    The right subtree of a node contains only nodes with keys greater than the node's key.

    Both the left and right subtrees must also be binary search trees.

*/

#include <climits>
#include <stack>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// not efficient
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return !root || 
            (!root->left || (isValidBST(root->left) && root->val > maxVal(root->left)))      // strictly greater
        && (!root->right || (isValidBST(root->right) && root->val < minVal(root->right)));  // strictly smaller
    }
private:
    int maxVal(TreeNode* root)
    {
        while (root->right)
            root = root->right;
        return root->val;
    }
    int minVal(TreeNode* root)
    {
        while (root->left)
            root = root->left;
        return root->val;
    }
};

// inorder traversal, keep track of the pre node
class Solution2 {
public:
    TreeNode *pre = nullptr;
    bool isValidBST(TreeNode *root) {
        if (!root)
            return true;
        if (!isValidBST(root->left))
            return false;
        if (pre && pre->val >= root->val)
            return false;
        pre = root;
        return isValidBST(root->right);
    }
};

class Solution3 {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode *pre = nullptr, *cur = root;
        stack<TreeNode*> stk;
        while (true)
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            if (stk.empty())
                break;
            cur = stk.top();
            if (pre && pre->val >= cur->val)
                return false;
            pre = cur;
            stk.pop();
            cur = cur->right;
        }
        return true;
    }
};

// note: shouldn't return in the middle, because we haven't restore the tree structure!!!!!!!!!!!!!!
class Solution4 {
public:
    bool isValidBST(TreeNode *root) {
        TreeNode *pre = nullptr, *cur = root, *temp;
        bool result = true;
        while (cur)
        {
            if (cur->left)
            {
                temp = cur->left;
                while (temp->right && temp->right != cur)
                    temp = temp->right;
                if (!temp->right)
                {
                    temp->right = cur;
                    cur = cur->left;
                }
                else
                {
                    if (pre->val >= cur->val)  // pre == temp
                        result = false;
                    temp->right = nullptr;
                    pre = cur;
                    cur = cur->right;
                }
            }
            else
            {
                if (pre && pre->val >= cur->val)
                    result = false;
                pre = cur;
                cur = cur->right;
            }
        }
        return result;
    }
};