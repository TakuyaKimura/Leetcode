/*

Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, 
and all nodes in the last level are as far left as possible. 
It can have between 1 and 2h nodes inclusive at the last level h.

*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// divide-and-conquer, 172ms
// will have at most one non-perfect binary subtree
// at each level, walk through the edge 4 times (first level only twice)
// 2*logn + 4*(logn - 1) + ... + 4*1
// O((log n)^2)
class Solution {
public:
    int countNodes(TreeNode* root) {
        int leftHeight = 0, rightHeight = 0;
        for (TreeNode *cur = root; cur; cur = cur->left)
            ++leftHeight;
        for (TreeNode *cur = root; cur; cur = cur->right)
            ++rightHeight;
        if (leftHeight == rightHeight)
            return (1 << leftHeight) - 1;
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};

// binary search - search for the last node, 76ms
// draw a tree to see the total numbers of nodes

// we use the fact that:
// for a perfect binary tree (every level is full)
// (number of nodes on level n) - 1 == number of nodes from level 1 through level n - 1
// so the big triangle == small triangle * 2 + 1

// result is the number of nodes up to "visit"
// for example: if on level 5, result is 26 (1, *2+1, *2, *2+1, *2)
// and there are 5 nodes not counted at this level
// when move on to next level, we can add 5 then substract 10
// that is: the triangle is 26 + 5, so the big triangle - 1 is (26+5)*2
// up to the next "visit", if turn left (26+5)*2 - 10, which is exactly 26 * 2
//                         if turn right, 26 * 2 + 1

// O((log n)^2), the same as the recursive solution
// but the recursive has a constant factor of 4, this is 1
class Solution2 {
public:
    int countNodes(TreeNode* root) {
        if (!root)
            return 0;
        int result = 1, height = 0, rTreeH;
        for (TreeNode *cur = root; cur; cur = cur->left)
            ++height;
        while (--height)
        {
            result *= 2;  // or <<= 1
            rTreeH = 0;
            for (TreeNode *cur = root->right; cur; cur = cur->left)
                ++rTreeH;
            if (rTreeH < height)
                root = root->left;
            else
            {
                root = root->right;
                result += 1;  // or |= 1
            }
        }
        return result;
    }
};