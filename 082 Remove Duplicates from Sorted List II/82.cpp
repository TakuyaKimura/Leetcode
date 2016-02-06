/*

Given a sorted linked list, delete all nodes that have duplicate numbers, 
leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// use double pointer
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode **pp = &head, *next;
        int cmp;
        while (*pp)
        {
            cmp = (*pp)->val;
            next = (*pp)->next;
            if (next && next->val == cmp)
            {
                while (next && next->val == cmp)
                    next = next->next;
                *pp = next;
            }
            else
                pp = &(*pp)->next;
        }
        return head;
    }
};

class Solution2 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode **runner = &head, *temp, *dlt;
        int runnerVal;

        if (!head || !head->next)
            return head;

        while (*runner)
        {
            runnerVal = (*runner)->val;
            if ((*runner)->next && (*runner)->next->val == runnerVal)
            {
                temp = *runner;
                while (temp && runnerVal == temp->val)
                {
                    dlt = temp;
                    temp = temp->next;
                    delete dlt;
                }
                *runner = temp;               // change the value, so can change the value of head
            }
            else
                runner = &((*runner)->next);  // move the pointer (instead of pointing to address of head)
        }
        return head;
    }
};

class Solution3 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *pre = &dummy, *cur = head, *next;
        int cmp;
        while (cur)
        {
            cmp = cur->val;
            next = cur->next;
            if (next && next->val == cmp)
            {
                while (next && next->val == cmp)
                    next = next->next;
                pre->next = next;
                cur = next;
            }
            else
            {
                pre = cur;
                cur = next;
            }
        }
        return dummy.next;
    }
};

class Solution4 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *pre = &dummy, *cur = head, *first = head;
        while (cur)
        {
            if (cur->val != first->val)
            {
                if (first->next == cur)
                {
                    pre = first;
                    first = cur;
                }
                else
                {
                    deleteBetween(pre, cur);
                    first = cur;
                }
            }
            cur = cur->next;
        }
        if (first && first->next)
            deleteBetween(pre, nullptr);
        return dummy.next;
    }
private:
    void deleteBetween(ListNode *pre, ListNode *next) {
        ListNode *cur = pre->next;
        ListNode *temp;
        while (cur != next)
        {
            temp = cur;
            cur = cur->next;
            delete temp;
        }
        pre->next = next;
    }
};