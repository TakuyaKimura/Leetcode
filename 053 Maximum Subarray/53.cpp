/*

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

More practice:
If you have figured out the O(n) solution,
try coding another solution using the divide and conquer approach, which is more subtle.

*/

#include <vector>
#include <algorithm>
using namespace std;

// dp, constant space
class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {
        int max = INT_MIN, pre = 0;
        for (auto num : nums)
        {
            if (pre < 0)
                pre = num;
            else
                pre += num;
            if (pre > max)
                max = pre;
        }
        return max;
    }
};

// dp, O(n) space
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN, n = nums.size();
        vector<int> sum(n + 1, 0);  // sum[i] = largest sum ending after ith number
        for (int i = 0; i < n; ++i)
        {
            sum[i + 1] = max(sum[i] + nums[i], nums[i]);
            maxSum = max(maxSum, sum[i + 1]);
        }
        return maxSum;
    }
};

// divide-and-conquer
class Solution3 {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty())
            return INT_MIN;
        return maxSum(nums, 0, nums.size() - 1);
    }
private:
    int maxSum(vector<int>& nums, int left, int right) {
        if (left == right)
            return nums[left];
        int mid = left + (right - left) / 2;
        int sum = max(maxSum(nums, left, mid), maxSum(nums, mid + 1, right));
        int leftMiddle = nums[mid], rightMiddle = nums[mid + 1], i, tempSum;
        for (i = mid - 1, tempSum = nums[mid]; i >= left; --i)
        {
            tempSum += nums[i];
            leftMiddle = max(leftMiddle, tempSum);
        }
        for (i = mid + 2, tempSum = nums[mid + 1]; i <= right; ++i)
        {
            tempSum += nums[i];
            rightMiddle = max(rightMiddle, tempSum);
        }
        return max(leftMiddle + rightMiddle, sum);
    }
};