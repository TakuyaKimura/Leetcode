/*

Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. 
It doesn't matter what you leave beyond the new length.

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size(), i, j;
        for (i = j = 2; j < n; ++j)
            if (nums[j] != nums[i - 2])  // if we put j at i, then nums[i] has to be != nums[i-2]
                nums[i++] = nums[j];
        return min(i, n);
    }
};