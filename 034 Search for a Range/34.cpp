/*

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = search(nums, target);
        if (left == nums.size() || nums[left] != target)
            return{ -1, -1 };
        return{ left, search(nums, target + 1) - 1 };
    }
private:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size(), mid;  // can't assign to nums.size() - 1, may return 0, and we need to substract 1
        while (left < right)  // can't be <= , because when equal, and assign mid to right, won't break out of the loop
        {                     // could use the latter middle element to solve this issue
            mid = (left + right) / 2;
            if (nums[mid] >= target)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};

class Solution2 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = 0, end = nums.size(), mid, left, right;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (nums[mid] >= target)
                end = mid;
            else
                start = mid + 1;
        }
        left = start;

        end = nums.size();
        while (start < end)
        {
            mid = (start + end) / 2;
            if (nums[mid] > target)
                end = mid;
            else
                start = mid + 1;
        }
        right = start;  // one-pass-the-last
        return left == right ? vector<int>{ -1, -1 } : vector<int>{ left, right - 1 };
    }
};

class Solution3 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = left(nums, target);
        if (nums[low] != target)
            return{ -1, -1 };
        return{ low, right(nums, target) };
    }
private:
    int left(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid;
        while (low < high)
        {
            mid = low + (high - low) / 2;
            if (nums[mid] >= target)
                high = mid;             
            else
                low = mid + 1;
        }
        return low;
    }
    int right(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid;
        while (low < high)
        {
            mid = low + ((high - low + 1) / 2);  // (low + high + 1) / 2
            if (nums[mid] <= target)
                low = mid;
            else
                high = mid - 1;
        }
        return high;
    }
};

// divide-and-conquer, O(logn)
// In the beginning of the search, as long as target is only in at most one of the two halves
// (so the other immediately stops), we have a single path.
// And if we ever come across the case where target is in both halves, then we split into two paths,
// but then each of those remains a single path. And both paths are only O(log n) long, so we have overall runtime O(log n).
class Solution4 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty())
            return{ -1, -1 };
        return search(nums, target, 0, nums.size() - 1);
    }
private:
    vector<int> search(vector<int>& nums, int target, int start, int end) {
        if (nums[start] == target && nums[end] == target)
            return{ start, end };
        if (target < nums[start] || target > nums[end])
            return{ -1, -1 };

        int mid = start + (end - start) / 2;
        vector<int> left = search(nums, target, start, mid);
        vector<int> right = search(nums, target, mid + 1, end);
        if (left[0] == -1)
            return right;
        if (right[0] == -1)
            return left;
        return{ left[0], right[1] }; 
    }
};

class Solution5 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto bounds = equal_range(nums.begin(), nums.end(), target);
        return *bounds.first != target ? vector<int>{ -1, -1 } :
            vector<int>{ bounds.first - nums.begin(), bounds.second - nums.begin() - 1 };
    }
};

class Solution6 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int lo = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if (nums[lo] != target)
            return vector<int>{ -1, -1 };
        int hi = upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
        return vector<int>{ lo, hi };
    }
};