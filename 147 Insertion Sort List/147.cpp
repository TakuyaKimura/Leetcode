/*

Sort a linked list using insertion sort.

*/

#include <climits>
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// use double pointer, 24ms
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode **cur = &head, **pp = &head, *tmp;
        while (*cur)
        {
            if ((*pp)->val > (*cur)->val)  // trick to speed up: only start from the beginning when necessary!!
                pp = &head;
            while ((*pp)->val < (*cur)->val)
                pp = &(*pp)->next;
            if (*pp != *cur)
            {
                tmp = *cur;
                *cur = tmp->next;  // put the next one
                tmp->next = *pp;
                *pp = tmp;
            }
            else
                cur = &(*cur)->next;
        }
        return head;
    }
};

// 24ms
class Solution2 {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(INT_MIN), *pre = &dummy, *next;
        while (head)
        {
            next = head->next;
            if (pre->val > head->val)  // trick to speed up: only start from the beginning when necessary!!
                pre = &dummy;
            while (pre->next && pre->next->val < head->val)
                pre = pre->next;
            head->next = pre->next;  // at first pre == dummy, whose next points to null
            pre->next = head;
            head = next;
        }
        return dummy.next;
    }
};

class Solution3 {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head)
            return nullptr;
        ListNode dummy(INT_MIN), *pre = head, *cur = head->next, *insert;
        dummy.next = head;
        head->next = nullptr;  // otherwise, will create loop
        while (cur)
        {
            if (cur->val < pre->val)  // trick to speed up: only start from the beginning when necessary!!
                pre = &dummy;

            insert = cur;
            cur = cur->next;
            while (pre->next && insert->val > pre->next->val)
                pre = pre->next;
            insert->next = pre->next;
            pre->next = insert;
        }
        return dummy.next;
    }
};

// 80ms
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(INT_MIN), *pre, *cur = head, *insert;
        while (cur)
        {
            insert = cur;
            cur = cur->next;
            pre = &dummy;
            while (pre->next && insert->val > pre->next->val)
                pre = pre->next;
            insert->next = pre->next;
            pre->next = insert;
        }
        return dummy.next;
    }
};

int main()
{
    Solution3 s;
    ListNode *head = new ListNode(1);
    ListNode *second = new ListNode(2);
    head->next = second;
    head = s.insertionSortList(head);
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
}