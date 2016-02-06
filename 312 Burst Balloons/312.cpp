/*

Given n balloons, indexed from 0 to n-1. 

Each balloon is painted with a number on it represented by array nums. 

You are asked to burst all the balloons. 

If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 

Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ¡Ü n ¡Ü 500, 0 ¡Ü nums[i] ¡Ü 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
    coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

*/

#include <vector>
#include <algorithm>
using namespace std;

// DP, O(n^3)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));  // dp[i][j] = max coins bursting balloons in the range (i, j) exlusive
        for (int k = 2; k < n; ++k)
            for (int left = 0; left < n - k; ++left)
            {
                int right = left + k, coins = 0;
                // for i to be the last bursted balloon in the range (left, right), left < i < right
                for (int i = left + 1; i < right; ++i)  //  since i is the last to burst, the two subproblems are independent
                    coins = max(coins, nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
                dp[left][right] = coins;
            }

        return dp[0][n - 1];
    }
};

// divide-and-conquer with memoization
class Solution2 {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return burst(nums, memo, 0, n - 1);
    }
private:
    int burst(vector<int>& nums, vector<vector<int>>& memo, int left, int right) {
        if (memo[left][right] != -1)
            return memo[left][right];

        int result = 0;
        for (int i = left + 1; i < right; ++i)
            result = max(result, nums[left] * nums[i] * nums[right] + burst(nums, memo, left, i) + burst(nums, memo, i, right));
        memo[left][right] = result;
        return result;
    }
};