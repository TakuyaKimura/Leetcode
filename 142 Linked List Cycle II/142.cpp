/*

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra spac

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }
        if (!fast || !fast->next)
            return nullptr;
        while (slow != head)
        {
            slow = slow->next;
            head = head->next;
        }
        return head;
    }
};

// same idea, just write the second part inside the first loop
class Solution2 {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                while (slow != head)
                {
                    slow = slow->next;
                    head = head->next;
                }
                return head;
            }
        }
        return nullptr;
    }
};