/*

Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

    1         3     3      2      1
     \       /     /      / \      \
      3     2     1      1   3      2
     /     /       \                 \
    2     1         2                 3

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

// dp[i][j] = trees containing nodes from i through j
// put a null in, because when root == start or end, we want the left or right child to be null
// i.e., dp[1][0], dp[2][1], ..., dp[n][n-1],
//       dp[2][1], dp[3][2], ..., dp[n+1][n] = {nullptr}
// but have to remember to remove the null before pushing trees in

// only need to create new nodes for roots
// other part of tree can share the same memory on the heap
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<vector<TreeNode*>>> dp(n + 2, vector<vector<TreeNode*>>(n + 2, { nullptr }));
        int gap, i, start, end, root;
        TreeNode *node;
        for (gap = 0; gap < n; ++gap)
            for (start = 1; start <= n - gap; ++start)
            {
                end = start + gap;
                dp[start][end] = {};  // remove the nullptr!!!!!!
                for (root = start; root <= end; ++root)
                    for (auto left : dp[start][root - 1])
                        for (auto right : dp[root + 1][end])
                        {
                            node = new TreeNode(root);  // have to create new node, can't just use the same node
                            node->left = left;
                            node->right = right;
                            dp[start][end].push_back(node);
                        }
            }
        return dp[1][n];
    }
};

// backtracking
// we can construct n node trees just from n-1 node trees
// we have two cases:
// 1) use the nth node as the new root, so newroot->left = oldroot; 
// 2) the nth node is not root, we traverse the old tree, 
//    every time the node in the old tree has a right child: old node->right = nth node, nth node ->left = right child; 
//    and when we reach the end of the tree, don't forget we also need to add the nth node here
class Solution2 {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result{ nullptr }, temp;
        TreeNode *node, *cur, *rightChild, *copy;
        for (int i = 1; i <= n; ++i)
        {
            for (auto tree : result)
            {
                node = new TreeNode(i);
                node->left = tree;  // put the entire the tree as the left child of the new node, don't need to clone, because we didn't modify it
                temp.push_back(node);
                if (!tree)
                    continue;
                cur = tree;
                while (cur->right)
                {
                    node = new TreeNode(i);
                    rightChild = cur->right;
                    cur->right = node;        // put the new node on the right
                    node->left = rightChild;  // put the previous right child as new node's left child
                    copy = clone(tree);
                    temp.push_back(copy);
                    cur->right = rightChild;  // recover
                    cur = cur->right;
                }
                cur->right = new TreeNode(i);
                copy = clone(tree);
                temp.push_back(copy);
                cur->right = nullptr;  // recover
            }
            result = temp;
            temp.clear();
        }
        return result;
    }
private:
    TreeNode* clone(TreeNode *root) {
        if (!root)
            return nullptr;
        TreeNode *copy = new TreeNode(root->val);
        copy->left = clone(root->left);
        copy->right = clone(root->right);
        return copy;
    }
};