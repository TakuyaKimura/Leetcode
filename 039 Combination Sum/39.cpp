/*

Given a set of candidate numbers (C) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, ¡­ , ak) must be in non-descending order. (ie, a1 ¡Ü a2 ¡Ü ¡­ ¡Ü ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
    [7]
    [2, 2, 3]

*/

#include <vector>
#include <algorithm>
using namespace std;

// recursion solution similar to Problem 78 Subsets

// time complexity O(k^n)? 
// each number can be chosen 0-k times (instead of 0-1), so it's actually (k+1)^n choices to make

// may need to remove the duplicates in candidates, so that the result won't have duplicates
//for (int i = 1; i < candidates.size();)
//    if (candidates[i] == candidates[i - 1])
//        candidates.erase(candidates.begin() + i);
//    else
//        ++i;

// backtracking
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> res;
        sort(candidates.begin(), candidates.end());
        recursiveSum(result, candidates, res, 0, target);
        return result;
    }
private:
    void recursiveSum(vector<vector<int>>& result, vector<int>& candidates, vector<int>& res, int idx, int target) {
        if (target == 0)
        {
            result.push_back(res);
            return;
        }
        int n = candidates.size(), candidate;
        for (int i = idx; i < n && (candidate = candidates[i]) <= target; ++i)
        {
            res.push_back(candidate);
            recursiveSum(result, candidates, res, i, target - candidate);  // can use multiple time, so not "i + 1"
            res.pop_back();  // pop it out before next iteration
        }
    }
};

// another backtracking
class Solution2 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> res;
        sort(candidates.begin(), candidates.end());
        recursiveSum(result, candidates, res, 0, target);
        return result;
    }
private:
    void recursiveSum(vector<vector<int>>& result, vector<int>& candidates, vector<int>& res, int idx, int target) {
        if (idx == candidates.size())
            return;
        if (target == 0)
        {
            result.push_back(res);
            return;
        }
        int candidate;
        if ((candidate = candidates[idx]) <= target)
        {
            res.push_back(candidate);
            recursiveSum(result, candidates, res, idx, target - candidate);  // either include it or not, make two function calls
            res.pop_back();
            recursiveSum(result, candidates, res, idx + 1, target);
        }
    }
};

// DP
class Solution3 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<vector<int>>> dp(target + 1, vector<vector<int>>());
        vector<vector<int>> comb;
        dp[0].push_back(vector<int>());
        for (int candidate : candidates)
            for (int k = candidate; k <= target; ++k)
            {
                comb = dp[k - candidate];
                if (!comb.empty())
                {
                    for (auto& vct : comb)
                        vct.push_back(candidate);
                    dp[k].insert(dp[k].end(), comb.begin(), comb.end());
                }
            }
        return dp[target];
    }
};