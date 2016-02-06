/*

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

      1
     / \
    2   3

The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

*/

#include <stack>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// dfs, preorder
class Solution2 {
public:
    int sumNumbers(TreeNode *root) {
        return sumAllLeafPath(root, 0);
    }
private:
    int sumAllLeafPath(TreeNode* root, int sum) {
        if (!root)
            return 0;
        sum = sum * 10 + root->val;
        if (!root->left && !root->right)
            return sum;
        return sumAllLeafPath(root->left, sum) + sumAllLeafPath(root->right, sum);
    }
};

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        int sum = 0;
        if (root)
            dfs(root, sum, 0);
        return sum;
    }
private:
    void dfs(TreeNode* root, int& sum, int tilParent) {
        tilParent = tilParent * 10 + root->val;
        if (!root->left && !root->right)
        {
            sum += tilParent;
            return;
        }
        if (root->left)
            dfs(root->left, sum, tilParent);
        if (root->right)
            dfs(root->right, sum, tilParent);
    }
};

// iterative, postorder
class Solution3 {
public:
    int sumNumbers(TreeNode* root) {
        int sum = 0, num = 0;
        TreeNode *last = nullptr, *temp;
        stack<TreeNode*> stk;
        while (true)
        {
            while (root)
            {
                stk.push(root);
                num = num * 10 + root->val;
                root = root->left;
            }
            if (stk.empty())
                break;
            temp = stk.top();
            if (temp->right && temp->right != last)  // don't pop yet
                root = temp->right;
            else
            {
                if (!temp->left && !temp->right)
                    sum += num;
                stk.pop();
                num /= 10;  // move up one level
                last = temp;
            }
        }
        return sum;
    }
};