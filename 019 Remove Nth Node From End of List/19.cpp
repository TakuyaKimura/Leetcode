/*

Given a linked list, remove the nth node from the end of list and return its head.

For example,
Given linked list: 1->2->3->4->5, and n = 2.
After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.
Try to do this in one pass.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *fast = &dummy, *slow = &dummy;
        for (int i = 0; i <= n; ++i)  // n+1 times
            fast = fast->next;
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        // slow is now the one before
        ListNode *temp = slow->next->next;
        delete slow->next;
        slow->next = temp;
        return dummy.next;
    }
};