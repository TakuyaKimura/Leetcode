/*

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. 
You may not modify the values in the list, only nodes itself can be changed.

*/

#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution2 {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode **pp = &head, *q;
        while (*pp && (q = (*pp)->next))
        {
            (*pp)->next = q->next;
            q->next = *pp;
            *pp = q;
            pp = &q->next->next;
        }
        return head;
    }
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;
        ListNode *pre = &dummy, *second;
        while (pre->next && (second = pre->next->next))
        {
            pre->next->next = second->next;
            second->next = pre->next;
            pre->next = second;
            pre = second->next;
        }
        return dummy.next;
    }
};

void printList(ListNode *head)
{
    while (head)
    {
        cout << head->val;
        head = head->next;
    }
}

int main()
{
    ListNode one = ListNode(1);
    ListNode two = ListNode(2);
    one.next = &two;
    Solution s;
    printList(s.swapPairs(&one));
}