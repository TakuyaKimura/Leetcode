/*

Given a singly linked list, group all odd nodes together followed by the even nodes. 
Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ...

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
	ListNode* oddEvenList(ListNode* head) {
		if (head)
		{
			ListNode *odd = head, *even = head->next, *evenHead = even;
			while (even && even->next)
			{
				odd = odd->next = even->next;
				even = even->next = odd->next;
			}
			odd->next = evenHead;
		}
		return head;
	}
};

class Solution2 {
public:
	ListNode* oddEvenList(ListNode* head) {
		ListNode odd(0), even(0), *tail[2]{ &odd, &even };
		for (int i = 0; head; i ^= 1, head = head->next)
			tail[i] = tail[i]->next = head;
		tail[0]->next = even.next;
		tail[1]->next = nullptr;  // don't need this if we use do {} while (head);
		return odd.next;
	}
};