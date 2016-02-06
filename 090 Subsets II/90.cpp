/*

Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:
    [
        [2],
        [1],
        [1,2,2],
        [2,2],
        [1,2],
        []
    ]

*/


#include <vector>
#include <algorithm>
using namespace std;

// without duplicates, an element is either in the subset or not
// with duplicates, an element is in the subset 0, 1, 2,..., count times

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int num, count, n = nums.size(), size, i = 0, j, k;
        vector<int> subset;
        vector<vector<int>> powerset{ {} };
        sort(nums.begin(), nums.end());  // need to sort
        while (i < n)
        {
            count = 1;  // reset the count
            num = nums[i];
            while (i + count < n && num == nums[i + count])
                ++count;
            size = powerset.size();
            for (j = 0; j < size; ++j)
            {
                subset = powerset[j];
                for (k = 0; k < count; ++k)
                {
                    subset.push_back(num);
                    powerset.push_back(subset);
                }
            }
            i += count;
        }
        return powerset;
    }
};