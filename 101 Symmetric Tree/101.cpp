/*

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

        1
       / \
      2   2
     / \ / \
    3  4 4  3

But the following is not:
        1
       / \
      2   2
       \   \
        3   3

Note:
Bonus points if you could solve it both recursively and iteratively.

*/

#include <queue>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursively
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        return !root || isMirrorEqual(root->left, root->right);
    }
private:
    bool isMirrorEqual(TreeNode *t1, TreeNode *t2) {
        if (!t1 && !t2)
            return true;
        if (!t1 || !t2)
            return false;
        return t1->val == t2->val && isMirrorEqual(t1->left, t2->right) && isMirrorEqual(t1->right, t2->left);
    }
};

// iteratively, one queue
class Solution2 {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root)
            return true;
        queue<TreeNode *> q;
        TreeNode *l, *r;
        q.push(root->left);
        q.push(root->right);
        while (!q.empty())
        {
            l = q.front();
            q.pop();
            r = q.front();
            q.pop();
            if (!l && !r)
                continue;      // look at the rest
            if (!l || !r || l->val != r->val)
                return false;
            q.push(l->left);
            q.push(r->right);  // note the order
            q.push(l->right);
            q.push(r->left);
        }
        return true;
    }
};

// two queues, slower
class Solution3 {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> leftNodes, rightNodes;
        TreeNode *left, *right;
        leftNodes.push(root);
        rightNodes.push(root);
        while (!leftNodes.empty())
        {
            left = leftNodes.front();
            right = rightNodes.front();
            leftNodes.pop();
            rightNodes.pop();
            if (!left && !right)
                continue;
            if (!left || !right || left->val != right->val)
                return false;
            leftNodes.push(left->left);
            leftNodes.push(left->right);
            rightNodes.push(right->right);
            rightNodes.push(right->left);
        }
        return true;
    }
};