/*

Given an array of integers, find out whether there are two distinct indices i and j in the array 
such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k.

*/

#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 48ms
// O(nlogk)
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0 || t < 0)
            return false;
        set<long long> window;
        set<long long>::iterator it;
        long long num;
        for (int i = 0; i < nums.size(); ++i)
        {
            num = nums[i];

            if (i > k)
                window.erase(nums[i - k - 1]);  // will add one back if there are duplicates, so it's fine

            // it = lower_bound(window.begin(), window.end(), num - t);  
                // this would exceed time limit for large inputs
                // On non-random-access iterators, the iterator advances cost additional O(n)

            // version below is log(n), binary search tree
            it = window.lower_bound(num - t);   // find the first not less than (greater or equal)
            if (it != window.end() && *it <= num + t)
                return true;

            window.insert(num);
        }
        return false;
    }
};

// 36ms, O(n)
// put [0...3] in the same bucket when t = 3, bucket_size = t + 1
// every bucket will only have one element if there's no duplicate
// whenever two nums fall into the same bucket, they are considered duplicates
// but also need to check the buckets immediately before and after

// [-3, 3], 1, 3
// A simple num / t just shrinks everything towards 0, we don't want this
// Therefore, we need to reposition every element
class Solution2 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0 || t < 0)  // t could be -1, which would make t+1==0
            return false;

        unordered_map<long long, long long> conversion;
        long long num, bucket;
        for (int i = 0; i < nums.size(); ++i)
        {
            num = (long long)nums[i] - INT_MIN;  // so everything is non-positive
            bucket = num / ((long long)t + 1);   // t could be INT_MAX or -1

            if (i > k)
                conversion.erase(((long long)nums[i - k - 1] - INT_MIN) / ((long long)t + 1));

            if (conversion.find(bucket) != conversion.end() ||
                conversion.find(bucket - 1) != conversion.end() && num - conversion[bucket - 1] <= t ||
                conversion.find(bucket + 1) != conversion.end() && conversion[bucket + 1] - num <= t)
                return true;

            conversion[bucket] = num;
        }
        return false;
    }
};

// 16ms, O(n^2)
class Solution3 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0 || t < 0)
            return false;
        const int N = nums.size();
        vector<int*> numptrs(N);
        for (int i = 0; i < N; ++i)
            numptrs[i] = &nums[i];
        sort(numptrs.begin(), numptrs.end(), cmpptr);

        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
            {
                //nums[i] and nums[j] is at most t
                if ((*numptrs[j]) > (*numptrs[i]) + t)
                    break;
                //the difference between i and j is at most k
                if (abs(numptrs[j] - numptrs[i]) <= k)  // difference in address
                    return true;
            }

        return false;
    }
private:
    static bool cmpptr(int* a, int* b) {
        return *a < *b;
    }
};