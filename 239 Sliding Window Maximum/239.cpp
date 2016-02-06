/*

Given an array nums, there is a sliding window of size k 
which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

    Window position                Max
    ---------------               -----
   [1  3  -1] -3  5  3  6  7       3
    1 [3  -1  -3] 5  3  6  7       3
    1  3 [-1  -3  5] 3  6  7       5
    1  3  -1 [-3  5  3] 6  7       5
    1  3  -1  -3 [5  3  6] 7       6
    1  3  -1  -3  5 [3  6  7]      7

Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ¡Ü k ¡Ü input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Hint:
How about using a data structure such as deque (double-ended queue)?
The queue size need not be the same as the window¡¯s size.
Remove redundant elements and the queue should store only elements that need to be considered.

*/

#include <vector>
#include <deque>
using namespace std;

// monotone priority queue
// imposes the restriction that a key (item) may only be inserted
// if its priority is greater than that of the last key extracted from the queue
// O(n) - each element is pushed and popped at most once
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> indices;  // only stores the indices
        vector<int> ans;
        int n = nums.size(), num;
        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            if (!indices.empty() && indices.front() == i - k)  // fall out of range
                indices.pop_front();
            while (!indices.empty() && nums[indices.back()] <= num)  // kick out the smaller ones
                indices.pop_back();
            indices.push_back(i);
            if (i >= k - 1)
                ans.push_back(nums[indices.front()]);  // the first element will be the largest
        }
        return ans;
    }
};