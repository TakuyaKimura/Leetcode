/*

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

*/

#include <vector>
using namespace std;

// there are only three cases:
// case 1: The leftmost element is less than the rightmost element, which means that the list is not rotated.
// case 2: The middle element is less than both leftmost and rightmost elements.
// case 3: The middle element is greater than both leftmost and rightmost elements.

// the minimum is at num[i] where num[i-1] > num[i]
// notice that if we subdivide the array into two, one will always be sorted, while the other contains the minimum
// for a sorted array that was rotated at least one step, num[low] must always be greater than num[high]

// use binary search, discard the sorted half, O(log n)

class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1, mid;
        while (start < end)
        {
            mid = (start + end) / 2;
            if (nums[mid] < nums[end])
                end = mid;
            else
                start = mid + 1;
        }
        return nums[start];
    }
};

//class Solution2 {
//public:
//    int findMin(vector<int>& nums) {
//        int low = 0, high = nums.size() - 1, mid;
//        if (nums[low] > nums[high])
//        {
//            while (low < high)
//            {
//                mid = (low + high) / 2;
//                if (nums[mid] < nums[high])
//                    high = mid;  // not "mid + 1", because num[mid] could be the min
//                else
//                    low = mid + 1;
//            }
//        }
//        return nums[low];
//    }
//};
//
//class Solution3 {
//public:
//    int findMin(vector<int>& nums) {
//        int start = 0, end = nums.size() - 1, mid;
//        while (nums[start] > nums[end])
//        {
//            mid = (start + end) / 2;
//            if (nums[mid] > nums[start])  // could compare to either nums[start] or nums[end]
//                start = mid + 1;
//            else
//            {
//                ++start;  // because nums[start] > nums[mid], can be discarded
//                end = mid;
//            }
//        }
//        return nums[start];
//    }
//};