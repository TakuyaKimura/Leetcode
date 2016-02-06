/*

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
    1
     \
      2
     /
    3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

*/

#include <vector>
#include <stack>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// iterative, using stack, O(n) space
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode *node = root;       
        while (true)
        {
            while (node)
            {
                stk.push(node);
                node = node->left;
            }
            if (stk.empty())
                break;
            node = stk.top();
            stk.pop();
            result.push_back(node->val);
            node = node->right;
        }
        return result;
    }
};

// iterative, Morris Traversal, O(1) space
// O(n) time, because every edge will be walked at most twice - once to find the predecessor, once to go to that node (cur)
class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode *pre, *cur = root;
        while (cur)
        {
            if (cur->left)
            {
                pre = cur->left;
                while (pre->right && pre->right != cur)  // stop when pre->right == cur to restore the tree structure
                    pre = pre->right;
                if (!pre->right)                         // add the link
                {
                    pre->right = cur;
                    cur = cur->left;                     // move to the left
                }
                else                                     // remove the link
                {
                    pre->right = nullptr;
                    result.push_back(cur->val);          // left subtree is done, so push the current
                    cur = cur->right;                    // move to the right   
                }
            }
            else
            {
                result.push_back(cur->val);
                cur = cur->right;
            }
        }
        return result;
    }
};

// recursive
class Solution3 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
private:
    void inorder(TreeNode* root, vector<int>& result) {
        if (root)
        {
            inorder(root->left, result);
            result.push_back(root->val);
            inorder(root->right, result);
        }
    }
};