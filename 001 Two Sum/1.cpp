/*

Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers 
such that they add up to the target, where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

*/

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// O(n) runtime, O(n) space
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> result(2);
        unordered_map<int, int> hash;
        int n = nums.size(), num;
        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            if (hash.find(target - num) != hash.end())
            {
                result[0] = hash[target - num];
                result[1] = i + 1;
                return result;
            }
            else
                hash[num] = i + 1;
        }
    }
};

// O(nlogn)
class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> sortedNums(nums.begin(), nums.end());
        sort(sortedNums.begin(), sortedNums.end());

        int val1, val2, n = nums.size(), i = 0, j = n - 1;
        // find two numbers added equals to target
        while (i < j)
        {
            if ((sortedNums[i] + sortedNums[j]) < target)
                ++i;
            else if ((sortedNums[i] + sortedNums[j]) > target)
                --j;
            else
            {
                val1 = sortedNums[i];
                val2 = sortedNums[j];
                break;
            }
        }

        vector<int> result(2);
        // find the index of the two numbers
        for (int i = 0, j = 0; j < 2; ++i)
            if (nums[i] == val1 || nums[i] == val2)
                result[j++] = i + 1;

        return result;
    }
};