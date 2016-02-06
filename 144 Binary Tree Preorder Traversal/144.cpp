/*

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
    1
     \
      2
     /
    3

return [1,2,3].

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
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode *node;
        if (root)
            st.push(root);
        while (!st.empty())
        {
            node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->right)  // push right child first
                st.push(node->right);
            if (node->left)
                st.push(node->left);
        }
        return result;
    }
};

// iterative, Morris Traversal, O(1) space
// still need to find the INORDER predecessor
// because when trying to break the link, we won't be able to find the PREORDER predecessor again
class Solution2 {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode *pre, *cur = root;
        while (cur)
        {
            if (cur->left)
            {
                pre = cur->left;
                while (pre->right && pre->right != cur)  // stop when pre->right == root to restore the tree structure
                    pre = pre->right;
                if (!pre->right)                         // add the link
                {
                    result.push_back(cur->val);          // print the root first
                    pre->right = cur;                 
                    cur = cur->left;
                }
                else                                     // remove the link
                {
                    pre->right = nullptr;
                    cur = cur->right;
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorder(root, result);
        return result;
    }
private:
    void preorder(TreeNode* root, vector<int>& result) {
        if (root)
        {
            result.push_back(root->val);
            preorder(root->left, result);
            preorder(root->right, result);
        }
    }
};