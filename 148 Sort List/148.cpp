/*

Sort a linked list in O(n log n) time using constant space complexity.

*/

#include <algorithm>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// the question requires O(nlogn) time, O(1) space
// bottom-up merge sort, no recursion
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        int n = count(head), blockSize, merged, aNum, bNum;
        ListNode **pp, *a, *b, *it, *temp;
        for (blockSize = 1; blockSize < n; blockSize *= 2)
        {
            pp = &head;
            it = head;
            merged = 0;
            while (merged < n)
            {
                a = it;
                aNum = min(n - merged, blockSize);
                merged += aNum;
                bNum = min(n - merged, blockSize);
                merged += bNum;
                if (bNum)
                {
                    while (--aNum)
                        it = it->next;
                    b = it->next;
                    it->next = nullptr;
                    it = b;
                    while (--bNum)
                        it = it->next;
                    temp = it->next;
                    it->next = nullptr;
                    it = temp;
                }
                while (a || b)
                {
                    if (!b || a && a->val <= b->val)
                    {
                        *pp = a;
                        a = a->next;
                    }
                    else
                    {
                        *pp = b;
                        b = b->next;
                    }
                    pp = &(*pp)->next;
                }
            }
        }
        return head;
    }
private:
    int count(ListNode* head) {
        int n;
        for (n = 0; head; ++n, head = head->next) {}
        return n;
    }
};

class Solution2 {
public:
    ListNode* sortList(ListNode* head) {
        int n = countNodes(head), blockSize = 1, mergedNum, aNum, bNum, i;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *A, *B, *last, *it, *temp;
        while (blockSize < n)
        {
            mergedNum = 0;
            last = &dummy;
            it = dummy.next;
            while (mergedNum < n)
            {
                aNum = min(n - mergedNum, blockSize);
                bNum = min(n - mergedNum - aNum, blockSize);
                A = it;                  // start of A
                if (bNum)
                {
                    for (i = 1; i < aNum; ++i)
                        it = it->next;   // last node of A
                    B = it->next;        // start of B
                    it->next = nullptr;  // end of A
                    it = B;
                    for (i = 1; i < bNum; ++i)
                        it = it->next;   // last node of B
                    temp = it->next;     // end of B
                    it->next = nullptr;
                    it = temp;
                }
                while (A || B)
                {
                    if (!B || A && A->val <= B->val)
                    {
                        last->next = A;
                        A = A->next;
                    }
                    else
                    {
                        last->next = B;
                        B = B->next;
                    }
                    last = last->next;
                }
                mergedNum += aNum + bNum;
            }
            blockSize *= 2;
        }
        return dummy.next;
    }
private:
    int countNodes(ListNode* head) {
        int count = 0;
        while (head)
        {
            ++count;
            head = head->next;
        }
        return count;
    }
};

// top-down merge sort, merge recursively, O(n) space since merge() takes care of one node at a time
class Solution3 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode *A = head, *B, *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        B = slow->next;
        slow->next = nullptr;
        return merge(sortList(A), sortList(B));
    }
private:
    // recursive
    ListNode* merge(ListNode* A, ListNode* B) {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->val <= B->val)
        {
            A->next = merge(A->next, B);
            return A;
        }
        else
        {
            B->next = merge(A, B->next);
            return B;
        }
    }
};

// top-down merge sort, merge iteratively, O(logn) space
class Solution4 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)  // at least two nodes
            return head;
        ListNode *A = head, *B, *slow = head, *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        B = slow->next;
        slow->next = nullptr;
        return merge(sortList(A), sortList(B));
    }
private:
    ListNode* merge(ListNode* A, ListNode* B) {
        //ListNode dummy(0);
        //ListNode* last = &dummy;
        //while (A || B)
        //{
        //    if (!B || A && A->val <= B->val)
        //    {
        //        last->next = A;
        //        A = A->next;
        //    }
        //    else
        //    {
        //        last->next = B;
        //        B = B->next;
        //    }
        //    last = last->next;
        //}
        //return dummy.next;
        ListNode *head, **p = &head;
        while (A || B)
        {
            if (!A)
            {
                *p = B;
                break;
            }
            if (!B)
            {
                *p = A;
                break;
            }
            if (A->val < B->val)
            {
                *p = A;
                A = A->next;
            }
            else
            {
                *p = B;
                B = B->next;
            }
            p = &(*p)->next;
        }
        return head;
    }
};

// quick sort, O(logn) space
// 2-way partition, but skip the duplicates when conquer the second half to pass the OJ
class Solution5 {
public:
    ListNode* sortList(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        quicksort(&dummy, nullptr);
        return dummy.next;
    }
private:
    // head and tail not inclusive
    void quicksort(ListNode* head, ListNode* tail) {
        if (head->next == tail)  // nothing in between
            return;
        ListNode *cur = head->next, *pivot = cur, *temp;
        int p = pivot->val;
        while (cur->next != tail)
        {
            if (cur->next->val < p)  // move it to the front, thus reversed the sequence to avoid sorted sequence being worst case
            {
                temp = head->next;
                head->next = cur->next;
                cur->next = cur->next->next;
                head->next->next = temp;
            }
            else
                cur = cur->next;
        }
        quicksort(head, pivot);

        // the trick to pass the OJ, don't really need it in 2-way partition implementation
        while (pivot->next != tail && pivot->next->val == p)
            pivot = pivot->next;

        quicksort(pivot, tail);  // tail recursion, without adding a new stack frame, but since we make two functional calls
                                 // we are still not using constant space
    }
};

class Solution6 {
public:
    ListNode* sortList(ListNode* head) {
        ListNode **p = &head;
        quicksort(p, nullptr);
        return head;
    }
private:
    void quicksort(ListNode** p, ListNode* tail) {
        if (*p == tail)
            return;
        ListNode *pivot = *p, **cur = &(*p)->next, *temp;
        int cmp = pivot->val;
        while (*cur != tail)
        {
            if ((*cur)->val < cmp)
            {
                temp = (*cur)->next;
                (*cur)->next = *p;
                *p = *cur;
                *cur = temp;
            }
            else
                cur = &(*cur)->next;
        }
        quicksort(p, pivot);
        while (pivot->next != tail && pivot->next->val == cmp)
            pivot = pivot->next;
        quicksort(&pivot->next, tail);  // tricky!!!!!!!!!!!!!!!!!!!!!!!!
    }
};

// quick sort, worst case O(n^2) space, average case O(nlogn) space
// 3-way partition, should work for lists with a lot duplicates, but won't pass OJ
class Solution7 {
public:
    ListNode* sortList(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        quicksort(&dummy, nullptr);
        return dummy.next;
    }
private:
    // head and tail not inclusive
    void quicksort(ListNode* head, ListNode* tail) {
        if (head->next == tail)
            return;
        ListNode *cur = head->next, *pivot = cur, *equal = pivot, *temp;
        while (cur->next != tail)
        {
            if (cur->next->val < pivot->val)
            {
                temp = head->next;
                head->next = cur->next;
                cur->next = cur->next->next;
                head->next->next = temp;
            }
            else if (cur->next->val == pivot->val)
            {
                temp = equal->next;
                equal->next = cur->next;
                cur->next = cur->next->next;
                //equal->next->next = temp;
                equal = equal->next;  // move equal to the back
                equal->next = temp;
            }
            else
                cur = cur->next;
        }
        quicksort(head, pivot);
        quicksort(equal, tail);  // tail recursion, without adding a new stack frame, but since we make two functional calls
                                 // we are still not using constant space
    }
};