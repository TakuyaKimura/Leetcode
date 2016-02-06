/*

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// recursive, return from the back so don't need a dummy head
class Solution3 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *cur = head, *temp = head;
        int i;
        for (i = 0; cur && i < k; ++i, cur = cur->next) {}
        if (i == k)
        {
            cur = reverseKGroup(cur, k);
            while (i--)
            {
                head = temp;
                temp = head->next;
                head->next = cur;
                cur = head;
                //head = temp;
            }
            //head = cur;
        }
        return head;
    }
};

// iterative
// can also count all the nodes, and substract k each time when we finish k nodes, but may overload if we have > INT_MAX nodes
class Solution2 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy = ListNode(-1), *pre = &dummy, *cur, *next;
        dummy.next = head;
        int i;
        while (true)
        {
            for (i = 0, cur = pre->next; cur && i < k; ++i, cur = cur->next) {}
            if (i < k)
                break;
            cur = pre->next;
            while (--i)
            {
                next = cur->next;
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
            }
            pre = cur;
        }
        return dummy.next;
    }
};

// use two double pointers
class Solution4 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode **p = &head, **q, *cur;
        int i;
        while (true)
        {
            for (i = 0, cur = *p; cur && i < k; ++i, cur = cur->next) {}
            if (i < k)
                break;
            q = &(*p)->next;
            while (--i)
            {
                cur = *q;
                *q = cur->next;
                cur->next = *p;
                *p = cur;
            }
            p = q;
        }
        return head;
    }
};

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode dummy = ListNode(-1), *last;
        dummy.next = head;
        int i = 0;
        while (head)
        {
            ++i;
            if (i % k == 0)
            {
                last = reverseBetween(last, head->next);
                head = last->next;
            }
            else
                head = head->next;
        }
        return dummy.next;
    }
private:
    // exlude pre and next
    ListNode *reverseBetween(ListNode *pre, ListNode *next)
    {
        ListNode *last = pre->next, *curr = last->next;
        // move every node to the front (after pre)
        while (curr != next)
        {
            last->next = curr->next;
            curr->next = pre->next;
            pre->next = curr;
            curr = last->next;
        }
        return last;
    }
};