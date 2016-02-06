/*

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. 
If there isn't one, return 0 instead.

Example 1:
	Given nums = [1, -1, 5, -2, 3], k = 3,
	return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
	Given nums = [-2, -1, 2, 1], k = 1,
	return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

Follow Up:
Can you do it in O(n) time?

*/

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// O(n)
class Solution {
public:
	int maxSubArrayLen(vector<int>& nums, int k) {
		int n = nums.size(), maxLen = 0, sum = 0;
		unordered_map<int, int> hash;
		for (int i = 0; i < n; ++i)
		{
			sum += nums[i];
			if (sum == k)
				maxLen = i + 1;
			else if (hash.find(sum - k) != hash.end())
				maxLen = max(maxLen, i - hash[sum - k]);  // hash[sum - k] got to be < i

			if (hash.find(sum) == hash.end())  // we only want to keep the first one (with the smallest i)
				hash[sum] = i;
		}
		return maxLen;
	}
};