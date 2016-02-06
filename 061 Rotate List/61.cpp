/*

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int len = 0;
        for (ListNode* cur = head; cur; ++len, cur = cur->next) {}
        if (len == 0 || (k %= len) == 0)
            return head;
        ListNode *slow = head, *fast = head;
        while (k--)
            fast = fast->next;
        while (fast->next)
        {
            fast = fast->next;
            slow = slow->next;
        }
        fast->next = head;
        head = slow->next;
        slow->next = nullptr;
        return head;
    }
};