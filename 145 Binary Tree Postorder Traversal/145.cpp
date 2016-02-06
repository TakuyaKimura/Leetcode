/*

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
    1
     \
      2
     /
    3

return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

*/

#include <vector>
#include <stack>
using namespace std;

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// print the node while pushing them onto stack
// go all the way to the right first
class Solution5 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode *node = root;
        while (true)
        {
            while (node)
            {
                result.push_back(node->val);  // then reverse at the end
                stk.push(node);
                node = node->right;  // go all the way to the right, because right child is the postorder predecessor of the root
            }
            if (stk.empty())
                break;
            node = stk.top()->left;
            stk.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// using two stacks
class Solution6 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s1, s2;
        TreeNode *node;
        if (root)
            s1.push(root);
        while (!s1.empty())
        {
            node = s1.top();
            s1.pop();
            s2.push(node);
            if (node->left)
                s1.push(node->left);
            if (node->right)
                s1.push(node->right);
        }
        while (!s2.empty())
        {
            result.push_back(s2.top()->val);
            s2.pop();
        }
        return result;
    }
};

// same idea, using one stack, then reverse the result vector (same rule as the second stack)
class Solution7 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode *node;
        if (root)
            stk.push(root);
        while (!stk.empty())
        {
            node = stk.top();
            stk.pop();
            result.push_back(node->val);
            if (node->left)
                stk.push(node->left);
            if (node->right)
                stk.push(node->right);  // so the right child is popped first, and pushed into result first
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// iterative, using stack, O(n) space
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode *cur = root, *justPopped = nullptr;
        do
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            while (!stk.empty())
            {
                cur = stk.top();
                if (!cur->right || cur->right == justPopped)
                {
                    stk.pop();
                    justPopped = cur;
                    result.push_back(cur->val);
                }
                else
                {
                    cur = cur->right;
                    break;
                }
            }
        } while (!stk.empty());

        return result;
    }
};

// same idea
class Solution2 {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode *cur = root, *justPop;
        if (root)
            st.push(root);
        while (!st.empty())
        {
            while (cur->left)
            {
                st.push(cur->left);
                cur = cur->left;
            }
            while (!st.empty())
            {
                cur = st.top();
                if (!cur->right || cur->right == justPop)  // no right child or just been popped
                {
                    st.pop();
                    justPop = cur;
                    result.push_back(cur->val);
                }
                else  // haven't pushed right child
                {
                    cur = cur->right;
                    st.push(cur);
                    break;
                }
            }
        }
        return result;
    }
};

// iterative, Morris Traversal, O(1) space
class Solution3 {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode dummy(0);
        dummy.left = root;
        TreeNode *pre, *temp, *cur = &dummy;
        while (cur)
        {
            if (cur->left)
            {
                pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;  // find the inorder predecessor
                if (!pre->right)
                {
                    pre->right = cur;  // add the link
                    cur = cur->left;
                }
                else
                {
                    reverse(cur->left, pre);
                    temp = pre;        // print from pre to cur->left
                    while (temp != cur->left)
                    {
                        result.push_back(temp->val);
                        temp = temp->right;
                    }
                    result.push_back(temp->val);  // cur->left
                    reverse(pre, cur->left);
                    pre->right = nullptr;  // break the link
                    cur = cur->right;  // now all the nodes on the left are printed, cur will be processed next time when we do reversing
                }
            }

            else  // !cur->left
                cur = cur->right;
        }
        return result;
    }

private:
    void reverse(TreeNode *from, TreeNode *to)
    {
        if (from == to)
            return;
        TreeNode *x = from, *y = from->right, *z;
        while (x != to)
        {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
        }
    }
};

// recursive
class Solution4 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postorder(root, result);
        return result;
    }
private:
    void postorder(TreeNode* root, vector<int>& result) {
        if (root)
        {
            postorder(root->left, result);
            postorder(root->right, result);
            result.push_back(root->val);
        }
    }
};