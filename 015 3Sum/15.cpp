/*

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ¡Ü b ¡Ü c)
The solution set must not contain duplicate triplets.
For example, given array S = {-1 0 1 2 -1 -4},

A solution set is:
(-1, 0, 1)
(-1, -1, 2)

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size(), i, j, k, target, sum, a, b, c;
        for (i = 0; i < n - 2; ++i)
        {
            if (i == 0 || nums[i] != a)
            {
                a = nums[i];
                target = -a;
                for (j = i + 1, k = n - 1; j < k;)
                {
                    b = nums[j];
                    c = nums[k];
                    sum = b + c;
                    if (sum == target)
                    {
                        result.push_back({ a, b, c });
                        while (++j < k && nums[j] == b) {}
                        while (--k > j && nums[k] == c) {}
                    }
                    else if (sum < target)
                        ++j;
                    else
                        --k;
                }
            }
        }
        return result;
    }
};