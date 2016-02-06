/*

Given an array of n integers nums and a target, find the number of index triplets i, j, k 

with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:

    [-2, 0, 1]
    [-2, 0, 3]

Follow up:
Could you solve it in O(n2) runtime?

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), first, result = 0;
        for (int i = 0; i < n - 2; ++i)
        {
            first = nums[i];
            for (int j = i + 1, k = n - 1; j < k;)
            {
                if (first + nums[j] + nums[k] < target)
                {
                    result += k - j;  // the third number could be any of the nums[j + 1] ... nums[k]
                    ++j;
                }
                else
                    --k;
            }
        }
        return result;
    }
};