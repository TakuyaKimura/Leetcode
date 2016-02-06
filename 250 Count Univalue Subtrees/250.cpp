/*

Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

For example:
Given binary tree,

           5
          / \
         1   5
        / \   \
       5   5   5

return 4.

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution2 {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        isEqual(root, count, 0);  // pass an arbitrary value
        return count;
    }
private:
    bool isEqual(TreeNode* root, int& count, int val) {
        if (!root)
            return true;

        // note: | not ||, so will not bypass any test
        if (!isEqual(root->left, count, root->val) | !isEqual(root->right, count, root->val))
            return false;

        ++count;
        return root->val == val;
    }
};

class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int count = 0;
        if (root)
            isUnival(root, count);
        return count;
    }
private:
    bool isUnival(TreeNode* root, int& count) {  // root is always valid
        bool leftIsUnival = true, rightIsUnival = true, equal = true;
        if (root->left)
        {
            leftIsUnival = isUnival(root->left, count);
            if (root->val != root->left->val)
                equal = false;
        }
        if (root->right)
        {
            rightIsUnival = isUnival(root->right, count);
            if (equal && root->val != root->right->val)
                equal = false;
        }

        if (equal && leftIsUnival && rightIsUnival)
        {
            ++count;
            return true;
        }
        return false;
    }
};