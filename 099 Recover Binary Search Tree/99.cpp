/*

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Morris in-order traversal using threading, O(1) space
// there could be either 1 or 2 disordered pairs
// [4,3] in 1 2 4 3 5
// or [6,3] [5,2] in 1 6 3 4 5 2 7, should swap 6 & 2
class Solution2 {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *pre, *cur = root, *first = nullptr, *second, *last = nullptr;  // last is the last one that's already in order
        while (cur)
        {
            if (!cur->left)
            {
                if (last && last->val > cur->val)  // may be the first one put in order, so last may haven't been set
                {
                    if (!first)
                        first = last;
                    second = cur;
                }
                last = cur;  // update the last
                cur = cur->right;
            }
            else
            {
                pre = cur->left;  // find the predecessor
                while (pre->right && pre->right != cur)
                    pre = pre->right;
                if (!pre->right)
                {
                    pre->right = cur;
                    cur = cur->left;
                }
                else
                {
                    pre->right = nullptr;
                    if (last->val > cur->val)  // last must have already been set
                    {
                        if (!first)
                            first = last;
                        second = cur;
                    }
                    last = cur;  // update the last
                    cur = cur->right;
                }
            }
        }
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
};

// recursion, 44ms
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *second, *pre = nullptr;
        inorder(root, first, second, pre);
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
private:
    void inorder(TreeNode* root, TreeNode*& first, TreeNode*& second, TreeNode*& pre) {
        if (!root)
            return;

        inorder(root->left, first, second, pre);

        if (pre && pre->val > root->val)
        {
            second = root;
            if (!first)
                first = pre;
            else
                return;  // can return early when found both nodes
        }
        pre = root;
            
        inorder(root->right, first, second, pre);
    }
};