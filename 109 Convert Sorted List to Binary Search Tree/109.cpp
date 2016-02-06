/*

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// inorder traversal, O(n) time, O(logn) space
// bottom-up, http://articles.leetcode.com/2010/11/convert-sorted-list-to-balanced-binary.html
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int len = listLength(head);
        ListNode *cur = head;
        return sortedListToBST(0, len - 1, cur);  // as if each node has index
    }
private:
    int listLength(ListNode* head) {
        int len = 0;
        while (head)
        {
            ++len;
            head = head->next;
        }
        return len;
    }
    TreeNode* sortedListToBST(int start, int end, ListNode*& cur) {
        if (start > end)
            return nullptr;
        int mid = start + (end - start) / 2;  // avoids overflow
        TreeNode *left = sortedListToBST(start, mid - 1, cur);
        TreeNode *root = new TreeNode(cur->val);
        root->left = left;
        cur = cur->next;           // move the pointer, O(n) total time
        root->right = sortedListToBST(mid + 1, end, cur);
        return root;
    }
};

// need to traverse the list every time to find the mid element
// top-down, slower than the above solution, O(nlogn) time
class Solution2 {
public:
    TreeNode* sortedListToBST(ListNode *head) {
        return sortedListToBST(head, nullptr);
    }
private:
    TreeNode* sortedListToBST(ListNode *head, ListNode *tail) {
        if (head == tail)
            return nullptr;
        ListNode *mid = head, *fast = head;
//        while (fast != tail && fast->next != tail)
        while (fast->next != tail && fast->next->next != tail)  // same, divide more evenly
        {
            mid = mid->next;
            fast = fast->next->next;
        }
        TreeNode *root = new TreeNode(mid->val);
        root->left = sortedListToBST(head, mid);
        root->right = sortedListToBST(mid->next, tail);
        return root;
    }
};