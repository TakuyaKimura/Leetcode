/*

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

*/

#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// see this post
// http://articles.leetcode.com/2011/04/construct-binary-tree-from-inorder-and-preorder-postorder-traversal.html

//         A         A
//        /    and    \
//       B             B
// the following are same for both trees:
//    Preorder Traversal = AB
//   Postorder Traversal = BA
// Level-Order Traversal = AB
// must have inorder to construct the tree


// a faster recursive (divide-and-conquer) than Solution2, 20ms
class Solution4 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size(), prePos = -1;
        unordered_map<int, int> hashMap;
        for (int i = 0; i < n; ++i)
            hashMap[inorder[i]] = i;
        return constructTree(inorder, preorder, 0, n - 1, prePos, hashMap);
    }
private:
    // left & right are for inorder, prePos just moves from left to right (do leftsubtree first)
    TreeNode* constructTree(vector<int>& inorder, vector<int>& preorder, int left, int right, int& prePos, unordered_map<int, int>& hashMap) {
        if (left > right)
            return nullptr;
        int value = preorder[++prePos], inPos = hashMap[value];

        // this is preorder traversal, that's why the prePos is always at the right place
        TreeNode *root = new TreeNode(value);
        root->left = constructTree(inorder, preorder, left, inPos - 1, prePos, hashMap);  // left first
        root->right = constructTree(inorder, preorder, inPos + 1, right, prePos, hashMap);

        return root;
    }
};

// iterative, 16ms
// walk through the preorder to add left child
// use stack to backtrack and add right child
class Solution5 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size(), pre = 1, in = 0;
        if (n == 0)
            return nullptr;
        TreeNode *p;
        stack<TreeNode*> stk;

        TreeNode *root = new TreeNode(preorder[0]);
        stk.push(root);

        while (true)  // or delete the break statement, use "while (pre < n)"
        {
            if (inorder[in] == stk.top()->val)
            {
                p = stk.top();
                stk.pop();
                ++in;
                if (in == n)
                    break;
                if (stk.empty() || inorder[in] != stk.top()->val)
                {
                    p->right = new TreeNode(preorder[pre]);
                    ++pre;
                    stk.push(p->right);
                }
            }
            else
            {
                p = new TreeNode(preorder[pre]);
                ++pre;
                stk.top()->left = p;
                stk.push(p);
            }
        }
        return root;
    }
};

// iterative, 16ms
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size(), pre = 1, in = 0;
        if (n == 0)
            return nullptr;
        TreeNode *newNode, *parent = nullptr, *root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        while (pre < n)
        {
            if (stk.empty() || stk.top()->val != inorder[in])  // "while" is also correct
            {
                newNode = new TreeNode(preorder[pre]);
                ++pre;
                if (!parent)
                    stk.top()->left = newNode;
                else  // means we've just pop some node off the stack, and the new node should be its right child
                {
                    parent->right = newNode;
                    parent = nullptr;
                }
                stk.push(newNode);
            }
            if (!stk.empty() && stk.top()->val == inorder[in])  // "while" is also correct
            {
                ++in;
                parent = stk.top();
                stk.pop();
            }
        }
        return root;
    }
};

// recursive (divide-and-conquer), 56ms
// Example: preorder = H BAFDCEG IKJ
//           inorder = ABCDEFG H IJK
// pre[0] - H
// nodes to the left of H in inorder are in the left subtree
// nodes to the right of H in inorder are in the right subtree
class Solution2 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        return builTreeHelper(preorder, 0, n, inorder, 0, n);
    }
private:
    // preEnd & inEnd are one past the last
    TreeNode* builTreeHelper(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd) {
        if (preStart == preEnd)
            return nullptr;
        TreeNode *root = new TreeNode(preorder[preStart]);
        int distance = find(inorder.begin() + inStart, inorder.begin() + inEnd, preorder[preStart]) - inorder.begin() - inStart;
        root->left = builTreeHelper(preorder, preStart + 1, preStart + 1 + distance, inorder, inStart, inStart + distance);
        root->right = builTreeHelper(preorder, preStart + 1 + distance, preEnd, inorder, inStart + distance + 1, inEnd);
        return root;
    }
};

// Note: this solution cannot pass OJ
// A more efficient way is to eliminate the search by using an efficient look-up mechanism such as hash table
// By hashing an element¡¯s value to its corresponding index in the inorder sequence
// we can do look-ups in constant time
// Now, we need only O(N) time to construct the tree, which theoretically is the most efficient way
class Solution3 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        mapToIndices(inorder);
        int n = preorder.size();
        return builTreeHelper(preorder, 0, n, inorder, 0, n);
    }

private:
    static const int MAX = 256;
    // a fast lookup for inorder's element -> index
    // binary tree's element must be in the range of [0, MAX-1]
    int mapIndex[MAX];
    void mapToIndices(vector<int>& inorder) {
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            //assert(0 <= inorder[i] && inorder[i] <= MAX - 1);
            mapIndex[inorder[i]] = i;
        }
    }

    // preEnd & inEnd are one past the last
    TreeNode* builTreeHelper(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd) {
        if (preStart == preEnd)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[preStart]);
        int distance = mapIndex[preorder[preStart]] - inStart;
        root->left = builTreeHelper(preorder, preStart + 1, preStart + 1 + distance, inorder, inStart, inStart + distance);
        root->right = builTreeHelper(preorder, preStart + 1 + distance, preEnd, inorder, inStart + distance + 1, inEnd);
        return root;
    }
};