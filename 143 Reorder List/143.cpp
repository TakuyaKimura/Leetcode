/*

Given a singly linked list L: L0¡úL1¡ú¡­¡úLn-1¡úLn,
               reorder it to: L0¡úLn¡úL1¡úLn-1¡úL2¡úLn-2¡ú¡­

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution2 {
public:
    void reorderList(ListNode *head) {
        if (!head)
            return;

        ListNode *head1 = head, *head2 = head->next, *preNode, *nextNode;

        // find the starting point of the second half
        while (head2 && head2->next)
        {
            head1 = head1->next;
            head2 = head2->next->next;
        }

        //reverse the second half
        head2 = head1->next; // the head of the second half
        head1->next = nullptr;
        preNode = nullptr;

        while (head2)
        {
            nextNode = head2->next;
            head2->next = preNode;
            preNode = head2;
            head2 = nextNode;
        }

        // merge the first half and the reversed second half
        head2 = preNode;
        head1 = head;

        while (head2)
        {
            nextNode = head1->next;
            head1 = head1->next = head2;  // exchange head1 and head2
            head2 = nextNode;              // so don't need to modify a lot of next pointers
        }
    }
};

class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head || !head->next)
            return;
        ListNode *slow = head, *fast = head, *last, *cur;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow is the last node of the left half
        // reverse the right half
        last = slow->next;
        cur = last->next;

        // put every cur after "slow"
        while (cur)
        {
            last->next = cur->next;
            cur->next = slow->next;
            slow->next = cur;
            cur = last->next;
        }

        // bring nodes on the right half to the left
        while (head != slow)
        {
            cur = head->next;  // store the next node
            head->next = slow->next;
            slow->next = slow->next->next;
            head->next->next = cur;
            head = cur;
        }
    }
};