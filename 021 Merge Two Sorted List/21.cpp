/*

Merge two sorted linked lists and return it as a new list. 
The new list should be made by splicing together the nodes of the first two lists.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        while (true)
        {
            if (!l1)
            {
                tail->next = l2;
                break;
            }
            if (!l2)
            {
                tail->next = l1;
                break;
            }
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        return dummy.next;
    }
};

// recursion
class Solution2 {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (!l1)
            return l2;
        if (!l2)
            return l1;
        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};

// use double pointer
class Solution3 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;
        ListNode **pp = &head;
        while (true)
        {
            if (!l1)
            {
                *pp = l2;
                break;
            }
            if (!l2)
            {
                *pp = l1;
                break;
            }
            if (l1->val < l2->val)
            {
                *pp = l1;
                l1 = l1->next;
            }
            else
            {
                *pp = l2;
                l2 = l2->next;
            }
            pp = &(*pp)->next;
        }

        return head;
    }
};