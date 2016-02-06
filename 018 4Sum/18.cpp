/*

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? 
Find all unique quadruplets in the array which gives the sum of target.

Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ¡Ü b ¡Ü c ¡Ü d)
The solution set must not contain duplicate quadruplets.
For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

A solution set is:
(-1,  0, 0, 1)
(-2, -1, 1, 2)
(-2,  0, 0, 2)

*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size(), i, j, k, m, a, b, c, d, target3, target2, sum;
        for (i = 0; i < n - 3 && nums[i] <= target / 4; ++i)
        {
            if (i != 0 && nums[i] == a)
                continue;
            a = nums[i];
            target3 = target - a;
            for (j = i + 1; j < n - 2 && nums[j] <= target3 / 3; ++j)
            {
                if (j != i + 1 && nums[j] == b)
                    continue;
                b = nums[j];
                target2 = target3 - b;
                for (k = j + 1, m = n - 1; k < m && nums[k] <= target2 / 2 && nums[m] >= target2 / 2;)
                {
                    c = nums[k];
                    d = nums[m];
                    sum = c + d;
                    if (sum == target2)
                    {
                        result.push_back({ a, b, c, d });
                        while (++k < m && nums[k] == c) {}
                        while (--m > k && nums[m] == d) {}
                    }
                    else if (sum < target2)
                        while (++k < m && nums[k] == c) {}
                    else
                        while (--m > k && nums[m] == d) {}
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> num{ 1, 0, -1, 0, -2, 2 };
    int target = 0;
    vector<vector<int>> result = s.fourSum(num, target);
    for (int i = 0; i < result.size(); ++i)
        for (int j = 0; j < result[i].size(); ++j)
            cout << result[i][j];
}