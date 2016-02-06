/*

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ¡Ü m ¡Ü n ¡Ü length of list.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy = ListNode(0);
        dummy.next = head;
        ListNode *pre = &dummy;
        for (int i = 1; i < m; ++i)
            pre = pre->next;
        ListNode *first = pre->next, *last = first->next;
        for (int i = m; i < n; ++i)
        {
            first->next = last->next;
            last->next = pre->next;
            pre->next = last;  // always put after pre
            last = first->next;
        }
        return dummy.next;
    }
};

class Solution3 {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode **last = &head;
        for (int i = 1; i < m; ++i)
            last = &(*last)->next;
        ListNode **first = &(*last)->next, *temp;  // not actually "first", the one after the first
        for (int i = m; i < n; ++i)
        {
            temp = *last;
            *last = *first;
            *first = (*first)->next;
            (*last)->next = temp;
        }
        return head;
    }
};

class Solution2 {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *leftTail = &dummy, *midHead, *rightHead, *p;
        for (int i = 1; i < m; ++i)
            leftTail = leftTail->next;  // node before the start point
        midHead = p = leftTail->next;
        rightHead = midHead->next;
        for (int i = m; i < n; ++i)
        {
            p = midHead;
            midHead = rightHead;
            rightHead = rightHead->next;  // store this node, b/c links are gonna be reversed
            midHead->next = p;
        }
        leftTail->next->next = rightHead;
        leftTail->next = midHead;
        return dummy.next;
    }
};