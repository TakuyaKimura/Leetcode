/*

Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 32ms
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *pre = &dummy, *temp, *cur;
        while (pre)
        {
            cur = pre->next;
            while (cur && cur->val == val)
            {
                temp = cur;
                cur = cur->next;
                delete temp;
            }
            pre->next = cur;
            pre = cur;
        }
        return dummy.next;
    }
};

// recursion, 36ms
class Solution2 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head)
            return head;
        head->next = removeElements(head->next, val);
        // return head->val == val ? head->next : head;
        if (head->val == val)
        {
            ListNode *newHead = head->next;
            delete head;
            return newHead;
        }
        else
            return head;
    }
};

// double pointer, 32ms
class Solution3 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode **pp = &head, *p;
        while (*pp)
        {
            p = *pp;
            if (p->val == val)
            { /* found one */
                *pp = p->next;
                delete p;
            }
            else
                pp = &p->next;
        }
        return head;
    }
};

class Solution4 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *pre = &dummy, *cur = head;
        while (cur)
        {
            if (cur->val == val)
            {
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
            }
            else
            {
                pre = cur;
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};