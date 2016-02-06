/*

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

*/

#include <vector>
using namespace std;

// O(n) time, O(1) space
// the first missing positive number must be in the range [1 ... n+1]
// Put each number in its right place, 1 at nums[0], 2 at nums[1], ...
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int num : nums)
            while (num > 0 && num <= n && nums[num - 1] != num)  // while
                swap(nums[num - 1], num);
        for (int i = 0; i < n; ++i)
            if (nums[i] != i + 1)
                return i + 1;
        return n + 1;
    }
};