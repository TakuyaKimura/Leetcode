/*

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

*/

#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// recursive (divide-and-conquer), 20ms
// the last node in postorder is the root
// Example: postorder = ACEDGFB JKI H
//            inorder = ABCDEFG H IJK
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size(), postPos = n;
        unordered_map<int, int> hashMap;
        for (int i = 0; i < n; ++i)
            hashMap[inorder[i]] = i;
        return constructTree(inorder, postorder, 0, n - 1, postPos, hashMap);
    }
private:
    // left & right are for inorder, postPos just moves from right to left (do right subtree first)
    TreeNode* constructTree(vector<int>& inorder, vector<int>& postorder, int left, int right, int& postPos, unordered_map<int, int>& hashMap) {
        if (left > right)
            return nullptr;
        int value = postorder[--postPos], inPos = hashMap[value];

        // this is the reversed postorder traversal, that's why the postPos is always at the right place
        TreeNode *root = new TreeNode(value);
        root->right = constructTree(inorder, postorder, inPos + 1, right, postPos, hashMap);  // right first
        root->left = constructTree(inorder, postorder, left, inPos - 1, postPos, hashMap);

        return root;
    }
};

// iterative, 16ms
// it's the same with 105 inorder + preorder
// just iterate both postorder & inorder from the back
class Solution3 {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty())
            return nullptr;
        TreeNode *p;
        stack<TreeNode*> stk;

        TreeNode *root = new TreeNode(postorder.back());
        stk.push(root);
        postorder.pop_back();

        while (true)
        {
            if (inorder.back() == stk.top()->val)
            {
                p = stk.top();
                stk.pop();
                inorder.pop_back();
                if (inorder.empty())
                    break;
                if (!stk.empty() && inorder.back() == stk.top()->val)
                    continue;
                p->left = new TreeNode(postorder.back());
                postorder.pop_back();
                stk.push(p->left);
            }
            else
            {
                p = new TreeNode(postorder.back());
                postorder.pop_back();
                stk.top()->right = p;
                stk.push(p);
            }
        }
        return root;
    }
};

// iterative, 16ms
// it's the same with 105 inorder + preorder
// just iterate both postorder & inorder from the back
class Solution2 {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size(), post = n - 2, in = n - 1;
        if (n == 0)
            return nullptr;
        TreeNode *newNode, *parent = nullptr, *root = new TreeNode(postorder[n - 1]);
        stack<TreeNode*> stk;
        stk.push(root);
        while (post >= 0)
        {
            if (stk.empty() || stk.top()->val != inorder[in])
            {
                newNode = new TreeNode(postorder[post]);
                --post;
                if (!parent)
                    stk.top()->right = newNode;
                else  // means we've just pop some node off the stack, and the new node should be its left child
                {
                    parent->left = newNode;
                    parent = nullptr;
                }
                stk.push(newNode);
            }
            if (!stk.empty() && stk.top()->val == inorder[in])  // "if" is also correct
            {
                --in;
                parent = stk.top();
                stk.pop();
            }
        }
        return root;
    }
};