/*

Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:

    A:          a1 ¡ú a2
                        ¨K
                           c1 ¡ú c2 ¡ú c3
                        ¨J
    B:     b1 ¡ú b2 ¡ú b3

begin to intersect at node c1.


Notes:
    If the two linked lists have no intersection at all, return null.
    The linked lists must retain their original structure after the function returns.
    You may assume there are no cycles anywhere in the entire linked structure.
    Your code should preferably run in O(n) time and use only O(1) memory.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution2 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *ptrA = headA, *ptrB = headB;
        while (ptrA != ptrB)
        {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }
        return ptrA;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB)
            return nullptr;
        ListNode *tail = headA, *slow = headB, *fast = headB;
        while (tail->next)
            tail = tail->next;
        tail->next = headA;  // make A a circle
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }  // they will meet at some point on the circle, if there is a circle
           // the distance from this point to the intersection == distance from headB to intersection % length of loop
        if (!fast || !fast->next)
        {
            tail->next = nullptr;  // break the circle
            return nullptr;
        }
        slow = headB;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }  // they will meet at the intersection
        tail->next = nullptr;
        return slow;
    }
};