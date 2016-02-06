/*

Follow up for "Find Minimum in Rotated Sorted Array":

    What if duplicates are allowed?

    Would this affect the run-time complexity? How and why?

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

The array may contain duplicates.

*/

#include <vector>
using namespace std;

// worst case O(n)
class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, mid;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (nums[mid] < nums[end])
                end = mid;
            else if (nums[mid] > nums[end])
                start = mid + 1;
            else
                --end;
        }
        return nums[start];
    }
};

//class Solution2 {
//public:
//    int findMin(vector<int>& nums) {
//        int low = 0, high = nums.size() - 1, mid;
//        while (low < high && nums[low] >= nums[high])
//        {
//            mid = (low + high) / 2;
//            if (nums[mid] > nums[high])
//                low = mid + 1;
//            else if (nums[mid] < nums[low])
//                high = mid;
//            else  // nums[low] == nums[low] == nums[high]
//                ++low;
//        }
//        return nums[low];
//    }
//};