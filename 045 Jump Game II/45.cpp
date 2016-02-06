/*

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. 
(Jump 1 step from index 0 to 1, then 3 steps to the last index.)

*/

//#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

// kinda like BFS (level order traversal)
// find all the places reachable after each step

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size(), start = 0, end = 0, temp, steps = 0;
        for (; end < n - 1; ++steps)
        {
            temp = end;
            for (int i = end; i >= start && end < n - 1; --i)  // can break as soon as end reach n-1
                end = max(end, i + nums[i]);

            if (end == temp)  // making no progress, can't reach
                return INT_MAX;

            start = temp + 1;
        }
        return steps;
    }
};