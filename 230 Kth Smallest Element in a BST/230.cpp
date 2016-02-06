/*

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ¡Ü k ¡Ü BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often 
and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:
Try to utilize the property of a BST.
What if you could modify the BST node's structure?
The optimal runtime complexity is O(height of BST).

*/

#include <stack>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursive, binary search
// time complexity for counting nodes:
// to count a tree with k nodes T(k) = 2T(k/2) + 1 or T(k) = T(k-1) + 1
//                           so T(k) = O(k)
// at every level, we only need to count the left subtree
// so the best case: O(n/2) + O(n/4) + ... = O(n)
//   the worst case: O(n-1) + O(n-2) + ... = O(n^2)
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        // assume root is not null, otherwise nothing to return
        int count = countNodes(root->left);
        if (k <= count)
            return kthSmallest(root->left, k);
        else if (k > count + 1)
            return kthSmallest(root->right, k - count - 1);
        else
            return root->val;
    }
private:
    int countNodes(TreeNode* root) {
        if (!root)
            return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

// DFS inorder recursive
class Solution2 {
public:
    int kthSmallest(TreeNode* root, int k) {
        int num;
        inorder(root, k, num);
        return num;
    }
private:
    void inorder(TreeNode* root, int& k, int &num) {
        if (root->left)
            inorder(root->left, k, num);
        --k;
        if (k == 0)
            num = root->val;
        else if (root->right)
            inorder(root->right, k, num);
    }
};

// DFS inorder iterative
class Solution3 {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        TreeNode *cur = root;
        while (true)
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();  // assume tree is not empty
            --k;
            if (k == 0)
                return cur->val;
            stk.pop();
            cur = cur->right;
        }
    }
};

// What if you could modify the BST node's structure?
class Solution4 {
public:
    int kthSmallest(TreeNode* root, int k) {
        int rank = 1;
        return kthSmallest(buildTreeWithRank(root, rank), k);
    }

private:
    struct TreeNodeWithRank {
        int val;
        int rank;
        TreeNodeWithRank *left;
        TreeNodeWithRank *right;
        TreeNodeWithRank(int x) : val(x), rank(1), left(nullptr), right(nullptr) {}
    };

    TreeNodeWithRank* buildTreeWithRank(TreeNode *root, int& rank) {
        if (!root)
            return nullptr;
        TreeNodeWithRank* rootWithRank = new TreeNodeWithRank(root->val);
        rootWithRank->left = buildTreeWithRank(root->left, rank);
        rootWithRank->rank = rank;
        ++rank;
        rootWithRank->right = buildTreeWithRank(root->right, rank);
        return rootWithRank;
    }

    int kthSmallest(TreeNodeWithRank *root, int k) {
        if (k < root->rank)
            return kthSmallest(root->left, k);
        else if (k > root->rank)
            return kthSmallest(root->right, k);
        else
            return root->val;
    }
};