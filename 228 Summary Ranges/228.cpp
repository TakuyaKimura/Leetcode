/*

Given a sorted integer array without duplicates, return the summary of its ranges.

For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

*/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int start, end, n = nums.size(), i = 0;
        while (i < n)
        {
            start = end = i;
            while (end < n - 1 && nums[end] + 1 == nums[end + 1])
                ++end;
            if (end > start)
                result.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
            else
                result.push_back(to_string(nums[start]));
            i = end + 1;
        }
        return result;
    }
};