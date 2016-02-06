/*

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

*/

#include <vector>
using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size(), sign = 1;
        for (int i = 1; i < n; ++i, sign = -sign)
            if (sign * (nums[i - 1] - nums[i]) > 0)
                swap(nums[i - 1], nums[i]);
    }
};

class Solution2 {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i)
            if (i % 2 == (nums[i - 1] > nums[i]))
                swap(nums[i - 1], nums[i]);
    }
};

class Solution3 {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i)
            swap(nums[i], nums[i - (i % 2 ^ (nums[i - 1] < nums[i]))]);
    }
};