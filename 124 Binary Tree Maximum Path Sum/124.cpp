/*

Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node 
to any node in the tree along the parent-child connections. 

The path does not need to go through the root.

For example:
Given the below binary tree,

      1
     / \
    2   3

Return 6.

*/

#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        oneLeg(root, maxSum);  // not returning this
        return maxSum;
    }
// function to update the maxSum and return max sum from point below (includes the root)
private:
    int oneLeg(TreeNode* root, int& maxSum) {
        if (!root)
            return 0;
        int leftLeg = max(0, oneLeg(root->left, maxSum));  // prone to bug: if it's negative, we just ignore these nodes
        int rightLeg = max(0, oneLeg(root->right, maxSum));
        maxSum = max(maxSum, leftLeg + rightLeg + root->val);          // update this
        return (leftLeg > rightLeg ? leftLeg : rightLeg) + root->val;  // return this
    }
};