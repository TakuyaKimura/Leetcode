/*

A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ¡Ù num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -¡Þ.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

Note:
Your solution should be in logarithmic complexity.

*/

#include <vector>
using namespace std;

// find a local max with binary search
// compare the middle two elements
// O(lgn)

class Solution {
public:
    int findPeakElement(const vector<int>& num) {
        int low = 0, high = num.size() - 1, mid;
        while (low < high)
        {
            mid = (low + high) / 2;
            if (num[mid] < num[mid + 1])
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
};

// sequential search
// O(n)
class Solution2 {
public:
    int findPeakElement(const vector<int>& num) {
        int n = num.size(), i;
        for (i = 0; i < n - 1; ++i)
            if (num[i] > num[i + 1])  // didn't break last iteration, means nums[i - 1] < nums[i]
                break;
        return i;
    }
};