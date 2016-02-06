/*

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

           1
         /   \
        2     3
         \
          5

All root-to-leaf paths are:

["1->2->5", "1->3"]

*/

#include <vector>
#include <string>
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (root)
            dfs(root, "", result);
        return result;
    }
private:
    // node will always be valid
    void dfs(TreeNode* node, string path, vector<string>& result) {
        path = path + "->" + to_string(node->val);
        if (!node->left && !node->right)
            result.push_back(path.substr(2));
        if (node->left)
            dfs(node->left, path, result);
        if (node->right)
            dfs(node->right, path, result);
    }
};