/*

A linked list is given such that each node contains an additional random pointer 
which could point to any node in the list or null.

Return a deep copy of the list.

*/

// Definition for singly-linked list with a random pointer.
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head)
            return nullptr;
        RandomListNode *cur = head, *copy;
        while (cur)
        {
            copy = new RandomListNode(cur->label);
            copy->next = cur->next;
            cur->next = copy;
            cur = copy->next;
        }

        for (cur = head; cur; cur = cur->next->next)
            if (cur->random)
                cur->next->random = cur->random->next;

        cur = head;
        copy = head->next;
        head = copy;
        while (copy->next)
        {
            cur->next = copy->next;
            copy->next = copy->next->next;
            cur = cur->next;
            copy = copy->next;
        }
        cur->next = nullptr;

        return head;
    }
};

// brute force takes O(n^2) time
// because for each random pointer we have to traverse the copied list in O(n) time