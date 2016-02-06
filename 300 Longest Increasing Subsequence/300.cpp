/*

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. 

Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: 
Could you improve it to O(n log n) time complexity?

*/

#include <vector>
#include <algorithm>
using namespace std;

/**
    Another way to look at this problem with patience sorting

    Patience solitaire is a card game to deal cards into piles (use stack)
    Rule: can't place a higher-valued card onto a lowered-valued card.
    Goal: form as few piles as possible.

    Greedy algorithm: Place each card on leftmost pile that fits. (use binary search)
    Observation: At any stage, top cards of piles increase from left to right
                 Cards within a pile form a decreasing subsequence, not longest
    Actually, min number of piles = max length of an IS

    To construct one LIS:
    Each card maintains a pointer to top card in previous pile at time of insertion
    Follow pointers starting from the top card of the rightmost stack


    Patience sorting: repeatedly remove the smallest card from the n top cards
    worst case O(nlogn) running time
*/

// DP, O(n^2)
// LIS is a special case of edit-distance
// comparing to the sorted sequence, removing any duplicates
// Mismatch penalty = infinity; gap penalty = 1.
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), num, maxlen = 0, temp;
        vector<int> lens(n);
        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            temp = 0;
            for (int j = 0; j < i; ++j)
                if (nums[j] < num)
                    temp = max(lens[j], temp);
            maxlen = max(maxlen, ++temp);
            lens[i] = temp;
        }
        return maxlen;
    }
};

// Greedy, use binary search to speed up, O(nlogn)
// O(log1 + log2 + log3 + .. + logn) = O(logn!) = O(nlogn)
// since we are just returning the length, LIS is not actually the correct subsequence
class Solution2 {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> LIS;
        for (int num : nums)
            if (LIS.empty() || num > LIS.back())
                LIS.push_back(num);
            else
                *lower_bound(LIS.begin(), LIS.end(), num) = num;
        return LIS.size();
    }
};

// construct the actual LIS based on above solution
// use a vector to record the indices to LIS each num could go
// if there are multiple LIS, this returns the last one
// if we want to return the first one, just do Longest Decreasing Subsequence from the back!!!!!!!!!!!!!!!
class Solution3 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), idx, num;
        vector<int> LIS, indices(n);
        for (int i = 0; i < n; ++i)
        {
            num = nums[i];
            //if (LIS.empty() || num > LIS.back())
            //{
            //    indices[i] = LIS.size();
            //    LIS.push_back(num);
            //}
            //else
            //{
            //    idx = binarySearch(LIS, num);
            //    LIS[idx] = num;
            //    indices[i] = idx;
            //}
            idx = binarySearch(LIS, num);
            if (idx == LIS.size())  // if largest, will return 1+last index
                LIS.push_back(num);
            else
                LIS[idx] = num;
            indices[i] = idx;
        }

        idx = LIS.size() - 1;
        for (int i = n - 1; idx >= 0; --i)
            if (indices[i] == idx)
                LIS[idx--] = nums[i];

        return LIS.size();
    }

private:
    int binarySearch(vector<int>& LIS, int num) {
        int low = 0, high = LIS.size() - 1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (LIS[mid] < num)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }
};