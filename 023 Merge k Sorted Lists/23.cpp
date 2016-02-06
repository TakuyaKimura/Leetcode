/*

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

*/

#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// reuse mergeTwoLists
// O(nlogk), each time in while loop, n comparisons (total number of elements), logk loops
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;
        int len = lists.size(), i;
        while (len > 1)
        {
            for (i = 0; i < len / 2; ++i)
                lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
            len = (len + 1) / 2;
        }
        return lists.front();
    }
private:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //ListNode dummy(0), *tail = &dummy;
        //while (true)
        //{
        //    if (!l1)
        //    {
        //        tail->next = l2;
        //        break;
        //    }
        //    if (!l2)
        //    {
        //        tail->next = l1;
        //        break;
        //    }
        //    if (l1->val < l2->val)
        //    {
        //        tail->next = l1;
        //        l1 = l1->next;
        //    }
        //    else
        //    {
        //        tail->next = l2;
        //        l2 = l2->next;
        //    }
        //    tail = tail->next;
        //}
        //return dummy.next;

		ListNode *head, **pp = &head;
		while (true)
		{
			if (!l1)
			{
				*pp = l2;
				break;
			}
			if (!l2)
			{
				*pp = l1;
				break;
			}
			if (l1->val < l2->val)
			{
				*pp = l1;
				l1 = l1->next;
			}
			else
			{
				*pp = l2;
				l2 = l2->next;
			}
			pp = &((*pp)->next);
		}
		return head;
    }
};

// maintain a minheap (default is a maxheap)
// O(nlogk), at most k elements in the heap
class Solution2 {
    // custom comparator used to compare between two listNode pointers. 
    // note : all pointers to be compared is supposed to be valid pointers.

	// functor, or function object, is an object that can behave like a function
	// This is done by defining operator()() of the class.
    struct compare {
        bool operator() (const ListNode* a, const ListNode* b) const {
            return a->val > b->val;  // default is less-than, returns true if a goes before b, the last (biggest) will be popped
        }
    };

public:
    ListNode *mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;
        for (auto list : lists)
            if (list)
                minHeap.push(list);

        ListNode dummy = ListNode(-1), *tail = &dummy;
        while (!minHeap.empty())
        {
            tail->next = minHeap.top();
            minHeap.pop();
            tail = tail->next;
            if (tail->next && !minHeap.empty())  // if it's the last int the heap, then don't need to push again
                minHeap.push(tail->next);
        }
        return dummy.next;
    }
};

class Solution3 {
    struct compare {
        bool operator() (const ListNode* a, const ListNode* b) const {
            return a->val > b->val;  // default is less-than, returns true if a goes before b, the last (biggest) will be popped
        }
    };
public:
    ListNode *mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = nullptr, **it = &head;  // should initialize head
        priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;
        for (auto list : lists)
            if (list)
                minHeap.push(list);

        while (!minHeap.empty())
        {
            *it = minHeap.top();
            minHeap.pop();
			if ((*it)->next && !minHeap.empty())
                minHeap.push((*it)->next);
            it = &((*it)->next);
        }
        return head;
    }
};