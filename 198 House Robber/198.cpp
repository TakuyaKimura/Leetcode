/*

You are a professional robber planning to rob houses along a street. 

Each house has a certain amount of money stashed, 
the only constraint stopping you from robbing each of them is that adjacent houses have security system connected 
and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, 
determine the maximum amount of money you can rob tonight without alerting the police.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        vector<int> money(n + 2);  // money[i]: max money from robbing the first i-1 houses
        money[0] = 0;
        money[1] = 0;
        for (int i = 0; i < n; ++i)
            money[i + 2] = max(nums[i] + money[i], money[i + 1]);
        return money[n + 1];
    }
};


// same idea as DP, but just keep track of the last two results
class Solution2 {
public:
    int rob(vector<int> &nums) {
        int a = 0, b = 0, temp;
        for (auto& num : nums)
        {
            temp = max(a + num, b);
            a = b;
            b = temp;
        }
        return b;
    }
};