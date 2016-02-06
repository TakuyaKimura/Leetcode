/*

Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// O(n) time, O(1) space
// Reverse the first half while finding the middle, restore the first half while comparing
class Solution2 {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head, *pre = nullptr, *next, *temp;
        while (fast && fast->next)
        {
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
            temp->next = pre;
            pre = temp;
        }
        next = slow;
        if (fast)
            slow = slow->next;  // odd, slow is the middle one

        bool palindrome = true;
        while (slow)
        {
            if (slow->val != pre->val)
                palindrome = false;
            slow = slow->next;
            temp = pre;
            pre = pre->next;
            temp->next = next;
            next = temp;
        }
        return palindrome;
    }
};

// Recursion, O(n) time and  O(n) space
class Solution3 {
public:
    bool isPalindrome(ListNode* head) {
        return recursion(&head, head);
    }
private:
    bool recursion(ListNode **left, ListNode *right) {
        if (!right)
            return true;
        if (!recursion(left, right->next))
            return false;
        bool currentLayer = (*left)->val == right->val;
        *left = (*left)->next;  // use double ptr to change the value in the caller function
        return currentLayer;
    }
};

// same idea, use reference
class Solution4 {
public:
    bool isPalindrome(ListNode* head) {
        return recursion(head, head);
    }
private:
    bool recursion(ListNode*& left, ListNode* right) {
        if (!right)
            return true;
        if (!recursion(left, right->next))
            return false;
        bool currentLayer = left->val == right->val;
        left = left->next;
        return currentLayer;
    }
};

// O(n) time, O(1) space
// reverse the second half
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow is the middle (odd) or the right middle (even)
        ListNode *pre = nullptr, *curr = slow, *next;
        while (curr)
        {
            next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        // pre is the new head of the reversed second half
        while (pre)
        {
            if (pre->val != head->val)
                return false;
            pre = pre->next;
            head = head->next;
        }
        return true;
    }
};