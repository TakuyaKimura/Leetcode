/*

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:
    You may only use constant extra space.

For example,
Given the following binary tree,

        1
       /  \
      2    3
     / \    \
    4   5    7

After calling your function, the tree should look like:

        1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL

*/

// Definition for binary tree with next pointer.
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

// O(n) time O(1) space
class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *leftMost = root, *parent = nullptr, *pre = nullptr;
        while (leftMost)
        {   // if leftMost not set below, will break out of loop
            for (parent = leftMost, leftMost = nullptr; parent; parent = parent->next)
            {
                if (parent->left)
                    if (pre)
                        pre = pre->next = parent->left;
                    else
                        pre = leftMost = parent->left;

                if (parent->right)
                    if (pre)
                        pre = pre->next = parent->right;
                    else
                        pre = leftMost = parent->right;
            }
            pre = nullptr;
        }
    }
};