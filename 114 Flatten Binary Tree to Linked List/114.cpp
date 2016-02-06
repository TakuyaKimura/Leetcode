/*

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

        1
       / \
      2   5
     / \   \
    3   4   6

The flattened tree should look like:
    1
     \
      2
       \
        3
         \
          4
           \
            5
             \
              6

Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.

*/

// In-place, preorder, first 3 solutions

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// preorder, iteration
// top-down, for each node, attach the right child to its predecessor (rightmost node of the left subtree)
//                          then move the left subtree to the right
class Solution {
public:
    void flatten(TreeNode *root) {
        TreeNode *pre;
        while (root)
        {
            if (root->left)
            {
                pre = root->left;
                while (pre->right)
                    pre = pre->right;
                pre->right = root->right;  // attach the right child to its predecessor
                root->right = root->left;  // move the left subtree to the right
                root->left = nullptr;
            }
            root = root->right;
        }
    }
};

// preorder, recursion, bottom-up
class Solution2 {
public:
    void flatten(TreeNode *root) {
        if (!root)
            return;
        TreeNode *leftBranch = root->left, *rightBranch = root->right;
        flatten(leftBranch);
        flatten(rightBranch);
        root->left = nullptr;
        root->right = leftBranch;
        while (root->right)
            root = root->right;  // find the rightmost node of the leftBranch
        root->right = rightBranch;
    }
};

// preorder, another recursion, top-down
class Solution3 {
public:
    void flatten(TreeNode *root) {
        if (!root)
            return;
        TreeNode *rightBranch = root->right;
        if (pre)
            pre->right = root;
        pre = root;
        flatten(root->left);
        flatten(rightBranch);  // root became pre, its right child was changed in "flatten(root->left)", so can't use root->right
        root->left = nullptr;
    }
private:
    TreeNode *pre;
};

// inorder & postorder, recursion, top-down
class Solution4 {
public :
    TreeNode* flattenInorder(TreeNode *root)
    {
        if (!root)
            return nullptr;
        flattenInorder(root->left);
        if (!head)
            head = root;
        if (pre)
            pre->right = root;
        root->left = nullptr;
        pre = root;
        flattenInorder(root->right);
        return head;
    }

    TreeNode* flattenPostorder(TreeNode *root)
    {
        if (!root)
            return nullptr;
        flattenPostorder(root->left);
        flattenPostorder(root->right);
        if (!head)
            head = root;
        if (pre)
            pre->right = root;
        root->left = nullptr;
        root->right = nullptr;  // otherwise the last node would have its right subtree hanging there
        pre = root;
        return head;
    }
private:
    TreeNode *head, *pre;
};

// iterative inorder
// top-down, for each node, move itself to its predessor (rightmost node of the left subtree)
class Solution5 {
public:
    TreeNode* flattenInorder(TreeNode *root)
    {
        TreeNode *preRoot, *head = nullptr, *last = nullptr;
        while (root)
        {
            if (root->left)
            {
                preRoot = root->left;
                while (preRoot->right)
                    preRoot = preRoot->right;  // get the rightmost node of the left subtree
                preRoot->right = root;
                root = root->left;             // new root
                preRoot = preRoot->right;      // store the previous root
                preRoot->left = nullptr;       // !!!!!!!!!!!!!!!!!!!!!!!
                if (last)
                    last->right = root;        // kinda like rotating clockwise
            }
            else
            {
                if (!head)
                    head = root;
                last = root;                   // already linked as right child
                root = root->right;
            }
        }
        return head;
    }
};

// iterative postorder
class Solution6 {
public:
    TreeNode* flattenPostorder(TreeNode *root) {
        //if (!root)
        //    return nullptr;
        //TreeNode *head = nullptr;
        //TreeNode *last = nullptr;
        //TreeNode *preRoot;
        //while (root)
        //{
        //    if (root->left)
        //    {
        //        preRoot = root->left;
        //        while (preRoot->right)
        //            preRoot = preRoot->right;  // find the rightmost node of the left subtree
        //        preRoot->right = root->right;  // connect the right subtree there
        //        while (preRoot->right)
        //            preRoot = preRoot->right;  // find the rightmost node of the right subtree
        //        preRoot->right = root;         // connect the previous root there
        //        root = root->left;             // new root
        //        preRoot = preRoot->right;      // store the previous root
        //        preRoot->left = nullptr;
        //        preRoot->right = nullptr;
        //        if (last)
        //            last->right = root;        // rotate clockwise
        //    }
        //    else
        //    {
        //        if (root->right)
        //        {
        //            preRoot = root->right;
        //            while (preRoot->right)
        //                preRoot = preRoot->right;
        //            preRoot->right = root;
        //        }
        //        root = root->right;
        //    }
        //}
    }
};

// recursion with return value