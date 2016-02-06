/*

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Try to solve it in linear time/space.

Return 0 if the array contains less than 2 elements.

You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

*/

#include <vector>
#include <algorithm>
using namespace std;

// bucket sort, 8ms
// the largest gap can not be smaller than the ceiling of (max-min)/(n-1)
// which can be expressed as (max - min - 1) / (n - 1) + 1
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size(), idx;
        if (n < 2)
            return 0;
        // 1. Pick 2 elements(a, b), compare them. (say a > b)
        // 2. Update min by comparing(min, b)
        // 3. Update max by comparing(max, a)
        auto minmax = minmax_element(nums.begin(), nums.end());  // a pair of iterators, 3n/2 comparisons
        int minNum = *minmax.first, maxNum = *minmax.second;
        if (minNum == maxNum)
            return 0;
        // the smallest in kth bucket - the smallest in (k-1)th bucket == bucket_size
        int bucket_size = (maxNum - minNum - 1) / (n - 1) + 1;  // at least 1
        int bucket_num = (maxNum - minNum) / bucket_size + 1;  // e.g. [1, 34, 67, 100], need 4 buckets (1-33, 34-66, 67-99, 100)
        vector<pair<int, int>> mins_maxs(bucket_num, make_pair(INT_MAX, -1));  // non-negative, so -1 will do the job
        pair<int, int> min_max;
        for (int num : nums)
        {
            idx = (num - minNum) / bucket_size;
            min_max = mins_maxs[idx];
            if (num < min_max.first)
                mins_maxs[idx].first = num;
            if (num > min_max.second)
                mins_maxs[idx].second = num;
        }

        // or do it like in the next solution
        int gap = mins_maxs[0].second - minNum, pre = mins_maxs[0].second;  // the first is guaranteed not empty, because minNum would be in there
        for (int i = 1; i < bucket_num; ++i)
        {
            min_max = mins_maxs[i];
            if (min_max.second != -1)  // bucket not empty
            {
                if (min_max.first - pre > gap)
                    gap = min_max.first - pre;
                pre = min_max.second;
            }
        }
        return gap;
    }
};

// bucket sort, 12ms
// the largest gap can not be smaller than the ceiling of (max-min)/(n-1)
// pigeonhole principle
// http://cgm.cs.mcgill.ca/~godfried/teaching/dm-reading-assignments/Maximum-Gap-Problem.pdf
class Solution2 {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size(), idx;
        if (n < 2)
            return 0;
        auto minmax = minmax_element(nums.begin(), nums.end());
        int minNum = *minmax.first, maxNum = *minmax.second;
        if (minNum == maxNum)
            return 0;
        int bucket_size = (maxNum - minNum - 1) / (n - 1) + 1;  // or use type double
        // only difference is the number of buckets
        // n-1 buckets, n-2 numbers left, so at least one of them is empty, and that gap would be larger than bucket size
        // so they won't fall in the same bucket
        vector<pair<int, int>> mins_maxs(n - 1, make_pair(INT_MAX, -1));
        for (auto& num : nums)
        {
            if (num == minNum || num == maxNum)  // minNum and maxNum are not put into any bucket
                continue;
            idx = (num - minNum) / bucket_size;
            if (num < mins_maxs[idx].first)
                mins_maxs[idx].first = num;
            if (num > mins_maxs[idx].second)
                mins_maxs[idx].second = num;
        }
        int gap = 0, pre = minNum;
        for (auto& min_max : mins_maxs)
            if (min_max.second != -1)
            {
                if (min_max.first - pre > gap)
                    gap = min_max.first - pre;
                pre = min_max.second;
            }
        if (maxNum - pre > gap)
            gap = maxNum - pre;
        return gap;
    }
};

// radix sort, using std::stable_partition
// Rearranges the elements in such a way that 
// all the elements for which pred returns true precede all those for which it returns false
// pred - Unary function that accepts an element in the range as argument,
// and the value returned indicates whether the element is to be placed before
class Solution3 {
public:
    int maximumGap(vector<int>& nums) {
        for (unsigned bit = 0; bit < 31; ++bit)
            stable_partition(nums.begin(), nums.end(), [bit](int a) { return !(a & (1 << bit)); });
        int difference = 0;
        size_t n = nums.size();
        for (size_t i = 1; i < n; ++i)
            difference = max(difference, nums[i] - nums[i - 1]);
        return difference;
    }
};

// radix sort, implementing std::stable_partition
class Solution4 {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size(), difference = 0;
        vector<int> prev(n);
        for (int bit = 0, mask = 1; bit < 31; ++bit, mask <<= 1)
        {
            swap(prev, nums);
            int start = 0, end = n - 1;  // start & end shouldn't be of type size_t, because when n is 0, end has to be -1 at first
            for (int i = 0; start <= end; ++i)  // stop when start and end meet
            {   // stable sort
                if (!(prev[i] & mask))       // 0 at that bit
                    nums[start++] = prev[i];
                if (prev[n - i - 1] & mask)  // 1 at that bit
                    nums[end--] = prev[n - i - 1];
            }
        }
        for (int i = 1; i < n; ++i)
            difference = max(difference, nums[i] - nums[i - 1]);
        return difference;
    }
};