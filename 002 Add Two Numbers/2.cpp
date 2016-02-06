/*

You are given two linked lists representing two non-negative numbers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head, **pp = &head;
        int sum, carry = 0;
        while (l1 || l2 || carry)
        {
            sum = carry;
            if (l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            if (sum > 9)
            {
                sum -= 10;
                carry = 1;
            }
            else
                carry = 0;  // don't forget!!!!!

            *pp = new ListNode(sum);
            pp = &(*pp)->next;
        }
        return head;
    }
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(-1), *tail = &dummy;
        int carry = 0;
        while (l1 || l2 || carry)
        {
            if (l1)
            {
                carry += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                carry += l2->val;
                l2 = l2->next;
            }
            tail->next = new ListNode(carry % 10);
            tail = tail->next;
            carry /= 10;
        }
        return dummy.next;
    }
};