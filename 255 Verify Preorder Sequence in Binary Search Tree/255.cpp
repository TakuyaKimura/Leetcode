/*

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?

================================================================================================================

Follow up:
Verify postorder traversal sequence of a binary search tree.

Note:
Postorder is reversed reverse preorder, that is we do preorder but right child first, then reverse the whole sequence.

To verify postorder sequence, we reverse the sequence, and check the preorder using stack storing increasing values, 
which are the nodes that we can add left child to them.

*/

#include <vector>
#include <stack>
using namespace std;

// O(n) time, O(n) space
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        stack<int> stk;     // nodes that we can put right child to them
        stk.push(INT_MAX);  // sentinel, so don't need to check if stack is empty
        int n = preorder.size(), predecessor = INT_MIN;

        for (int num : preorder)
        {
            if (num < predecessor)
                return false;

            while (num > stk.top())  // put a right child
            {
                predecessor = stk.top();
                stk.pop();
            }

            stk.push(num);
        }
        return true;
    }
};

// O(n) time, O(1) space, modify the original array to mimic stack
class Solution2 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int n = preorder.size(), predecessor = INT_MIN, i = -1;

        for (int num : preorder)
        {
            if (num < predecessor)
                return false;

            while (i >= 0 && num > preorder[i])  // put a right child
                predecessor = preorder[i--];

            preorder[++i] = num;
        }
        return true;
    }
};

// divide-and-conquer, O(n^2) time, O(n) space
// too slow, can't pass OJ
class Solution3 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        return dfs(preorder, 0, preorder.size());
    }
private:
    bool dfs(vector<int>& preorder, int start, int end) {  // end is one pass the last one
        if (end - start < 3)
            return true;
        int root = preorder[start], i = start + 1, j;
        for (; i < end && preorder[i] < root; ++i) {}
        for (j = i; j < end; ++j)
            if (preorder[j] < root)
                return false;
        return dfs(preorder, start + 1, i) && dfs(preorder, i, end);
    }
};

// divide-and-conquer, O(n^2) time, O(n) space, barely pass OJ
class Solution4 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        return verifyPreorder(preorder, 0, preorder.size(), INT_MIN);
    }
private:
    bool verifyPreorder(vector<int>& preorder, int start, int end, int predecessor) {
        if (start == end)
            return true;

        int root = preorder[start], i = start + 1;
        if (root < predecessor)
            return false;

        for (; i < end && preorder[i] < root; ++i) {}

        if (!verifyPreorder(preorder, start + 1, i, predecessor))
            return false;

        return verifyPreorder(preorder, i, end, root);
    }
};