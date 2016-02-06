/*

Note: This is an extension of House Robber.

After robbing those houses on that street, 
the thief has found himself a new place for his thievery so that he will not get too much attention. 

This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. 
Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, 
determine the maximum amount of money you can rob tonight without alerting the police.

*/

#include <vector>
#include <algorithm>
using namespace std;

// 1 -> 2 -> 3 -> 1 becomes 2 -> 3 if 1 is not robbed
// house i not robbed, or house i + 1 not robbed, at least one of them
// chose i to be n and i + 1 to be 0 for simpler coding
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        return max(rob(nums, 0, n - 2), rob(nums, 1, n - 1));
    }
private:
    int rob(vector<int>& num, int first, int last) {
        int a = 0, b = 0, temp;
        for (int i = first; i <= last; ++i)
        {
            temp = max(a + num[i], b);
            a = b;
            b = temp;
        }
        return b;
    }
};