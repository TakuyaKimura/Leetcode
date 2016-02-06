/*

Reverse a singly linked list.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// iterative
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr, *cur = head, *next;
        while (cur)
        {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};

// recursive
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode *next = head->next;
        ListNode *newHead = reverseList(next);
        head->next = nullptr;
        next->next = head;
        return newHead;
    }
};