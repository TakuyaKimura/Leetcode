/*

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

*/

#include <vector>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursive
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return arrayRange(nums, 0, nums.size() - 1);
    }
private:
    TreeNode* arrayRange(vector<int>& nums, int lo, int hi)
    {
        if (lo > hi)
            return nullptr;
        int mid = lo + (hi - lo) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = arrayRange(nums, lo, mid - 1);
        root->right = arrayRange(nums, mid + 1, hi);
        return root;
    }
};

// iterative
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {

    }
};