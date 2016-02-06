/*

Given an array of n positive integers and a positive integer s, 
find the minimal length of a subarray of which the sum ¡Ý s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.


More practice:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

*/

#include <vector>
using namespace std;

// O(n)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = 0, sum = 0, start = 0, end = 0, n = nums.size();
        for (; end < n; ++end)
        {
            sum += nums[end];
            if (sum < s)
                continue;
            while (sum >= s)
                sum -= nums[start++];
            if (len > end - start + 2 || len == 0)
                len = end - start + 2;  // sum is now < s, we need to add one
        }
        return len;
    }
};

// binary search, O(n logn)
// accumulated sum is an strictly increasing array (like sorted, distinct)

class Solution2 {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size(), sum = 0, left, len = 0;
        vector<int> sums(n + 1, 0);
        for (int i = 0; i < n; ++i)
            sums[i + 1] = (sum += nums[i]);
        for (int i = 1; i <= n; ++i)
        {
            if (sums[i] < s)
                continue;
            left = binarySearch(sums, sums[i] - s, 0, i - 1);
            if (i - left < len || len == 0)
                len = i - left;
        }
        return len;
    }
private:
    int binarySearch(vector<int>& sums, int target, int start, int end) {
        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (sums[mid] == target)
                return mid;
            else if (sums[mid] < target)
                start = mid + 1;
            else
                end = mid - 1;
        }
        return end;
    }
};

class Solution3 {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size(), sum = 0, right, len = 0;
        vector<int> sums(n + 1, 0);
        for (int i = 0; i < n; ++i)
            sums[i + 1] = (sum += nums[i]);
        for (int i = 0; i < n; ++i)
        {
            right = binarySearch(sums, s + sums[i], i + 1, n);
            if (right <= n && (right - i < len || len == 0))  // if right > n means no number is large enough
                len = right - i;
        }
        return len;
    }
private:
    int binarySearch(vector<int>& sums, int target, int start, int end) {
        while (start <= end)
        {
            int mid = start + (end - start) / 2;
            if (sums[mid] == target)
                return mid;
            else if (sums[mid] < target)
                start = mid + 1;
            else
                end = mid - 1;
        }
        return start;
    }
};