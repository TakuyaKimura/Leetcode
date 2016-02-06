/*

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.

*/

#include <vector>
using namespace std;

// if duplicates are allowed
// comparing A[mid] with A[low] (or A[high]) sometimes fails to tell where the pivot is
// e.g., 115111111
// so the worst case is O(n)

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            if (nums[mid] == target)
                return true;
            // left half is in order
            if (nums[low] < nums[mid])                          // could also use nums[high]
            {
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // pivot is in the left half, right half is in order
            else if (nums[low] > nums[mid])
            {
                if (nums[mid] < target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            // nums[low] == nums[mid]
            // nums[low] is duplicated, it's safe to ignore it
            // or there are only two elements left
            else
                ++low;                                         // --high
        }
        return false;
    }
};

class Solution2 {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1, mid, i;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            if (nums[mid] == target)
                return true;
            // left half is in order
            if (nums[low] < nums[mid])
            {
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            // pivot is in the left half, right half is in order
            else if (nums[low] > nums[mid])
            {
                if (nums[mid] < target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            // nums[low] == nums[mid]
            else if (nums[mid] != nums[high])
                low = mid + 1;
            // nums[low] == nums[mid] == nums[high]
            else
            {
                // traverse from mid to both side, until find a different (it' ok to left out nums[high])
                for (i = 1; i <= mid - low; ++i)
                {
                    if (nums[mid - i] != nums[mid])
                    {
                        high = mid - i;  // can discard all on the right, because they are all the same
                        break;
                    }
                    if (nums[mid + i] != nums[mid])
                    {
                        low = mid + i;
                        break;
                    }
                }
                // all elements are the same, and is not equal to target
                if (i + low == mid + 1)
                    return false;
            }
        }
        return false;
    }
};