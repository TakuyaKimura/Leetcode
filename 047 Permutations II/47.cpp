/*

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
    [1,1,2], [1,2,1], and [2,1,1].

*/

#include <vector>
#include <algorithm>
using namespace std;

// note: 1) have to sort 2) don't swap back, need to avoid swapping the same number in the same loop
// take 1,1,2,2 as an example
// not swapping back makes sure that only one 2 swaps with 1 (with 2 in the start position)
// sorting makes sure that 1 won't be swapped to the start position again (all 1s are skipped before encountering 2)

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, nums.size(), res);
        return res;
    }
private:
    void dfs(vector<int> nums, int start, int end, vector<vector<int>>& res) {
        if (start == end)  // start == end - 1 is also correct, but need the return statement to skip the following for loop
        {
            res.push_back(nums);
            //return;
        }
        for (int i = start; i < end; ++i)
        {
            if (start != i && nums[start] == nums[i])
                continue;
            swap(nums[start], nums[i]);
            dfs(nums, start + 1, end, res);
        }
    }
};