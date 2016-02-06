/*

Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:
    [
        [3],
        [1],
        [2],
        [1,2,3],
        [1,3],
        [2,3],
        [1,2],
        []
    ]

*/

#include <vector>
#include <algorithm>
using namespace std;

// recursion solution similar to Problem 39 Combination Sum

// backtracking
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result{ {} };
        vector<int> subset;
        int size, i;
        sort(nums.begin(), nums.end());
        for (int num : nums)
        {
            size = result.size();
            for (i = 0; i < size; ++i)
            {
                subset = result[i];
                subset.push_back(num);
                result.push_back(subset);
            }
        }
        return result;
    }
};

// bit manipulation, Time complexity : O(n*2^n)
// each subset can be represented by an n-bit number, where each bit represents where the number is used
// e.g., when n = 2, 00, 01, 10, 11 are the 4 subsets
class Solution2 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size(), size = 1 << n, i, j, num;
        vector<vector<int>> result(size, vector<int>());
        sort(nums.begin(), nums.end());
        for (i = 0; i < n; ++i)
        {
            num = nums[i];
            for (j = 0; j < size; ++j)
                if (j >> i & 1)
                    result[j].push_back(num);
        }
        return result;
    }
};

class Solution3 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size(), size = 1 << n, i, j;
        vector<vector<int>> result(size, vector<int>());
        sort(nums.begin(), nums.end());
        for (j = 0; j < size; ++j)
            for (i = 0; i < n; ++i)
                if (j >> i & 1)
                    result[j].push_back(nums[i]);
        return result;
    }
};

// recursion
// traverse the decision tree (where each edge encodes either 0 or 1) of 2^n leaf nodes.
// Then, each path from the root to leaf is a binary bit vector of inclusion/exclusion of the set elements.
class Solution4 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> subset;
        sort(nums.begin(), nums.end());
        dfs(result, subset, nums, 0);
        return result;
    }
private:
    void dfs(vector<vector<int>>& result, vector<int>& subset, vector<int>& nums, int idx) {
        if (idx == nums.size())
        {
            result.push_back(subset);
            return;
        }
        subset.push_back(nums[idx]);
        dfs(result, subset, nums, idx + 1);  // either include it or not, make two function calls
        subset.pop_back();
        dfs(result, subset, nums, idx + 1);
    }
};

// another recursion
// imagine there are different levels of call function
// each level has different numbers of element in the subset
// i.e. 1st level has 0, 2nd level has 1, ...
class Solution5 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> subset;
        sort(nums.begin(), nums.end());
        dfs(result, subset, nums, 0);
        return result;
    }
private:
    void dfs(vector<vector<int>>& result, vector<int>& subset, vector<int>& nums, int idx) {
        for (int i = idx; i < nums.size(); ++i)
        {
            subset.push_back(nums[i]);  // go to the left child, representing "1"
            dfs(result, subset, nums, i + 1);
            subset.pop_back();         // go to the right child, representing "0"
        }
        result.push_back(subset);  // reach the leaf node, each leaf node is a subset
    }
};