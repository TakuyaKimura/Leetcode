/*

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        for (int i = 0, frontier = 0, n = nums.size(); i <= frontier; ++i)
        {
            frontier = max(frontier, nums[i] + i);
            if (frontier >= n - 1)
                return true;
        }
        return false;
    }
};