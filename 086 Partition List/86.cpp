/*

Given a linked list and a value x, partition it 
such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution2 {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *left, *right, **p = &left, **q = &right;  // in OJ, have to initialize at least right to nullptr
        while (head)
        {
            if (head->val < x)
            {
                *p = head;
                p = &head->next;
            }
            else
            {
                *q = head;
                q = &head->next;
            }
            head = head->next;
        }
        *p = right;
        *q = nullptr;
        return left;
    }
};

class Solution3 {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *right = nullptr, **p = &head, **q = &right;  // in OJ, have to initialize at least right to nullptr
        while (*p)
        {
            if ((*p)->val < x)
                p = &(*p)->next;
            else
            {
                *q = *p;
                *p = (*p)->next;
                q = &(*q)->next;
            }
        }
        *p = right;
        *q = nullptr;
        return head;
    }
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode leftHead = ListNode(-1), rightHead = ListNode(-1);
        ListNode *leftTail = &leftHead, *rightTail = &rightHead;
        while (head)
        {
            if (head->val < x)
            {
                leftTail->next = head;
                leftTail = leftTail->next;
            }
            else
            {
                rightTail->next = head;
                rightTail = rightTail->next;
            }
            head = head->next;
        }
        leftTail->next = rightHead.next;
        rightTail->next = nullptr;    // otherwise creates loop
        return leftHead.next;
    }
};