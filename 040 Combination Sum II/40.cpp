/*

Given a collection of candidate numbers (C) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
    All numbers (including target) will be positive integers.
    Elements in a combination (a1, a2, ¡­ , ak) must be in non-descending order. (ie, a1 ¡Ü a2 ¡Ü ¡­ ¡Ü ak).
    The solution set must not contain duplicate combinations.

For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
    [1, 7]
    [1, 2, 5]
    [2, 6]
    [1, 1, 6]

*/

#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// 1,2,2
// 1,2   = 3
// 1,  2 = 3
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> comb;
        dfs(candidates, result, comb, target, 0, candidates.size());
        return result;
    }
private:
    void dfs(vector<int>& candidates, vector<vector<int>>& result, vector<int>& comb, int target, int start, int n) {
        if (target == 0)
        {
            result.push_back(comb);
            return;
        }
        int candidate;
        for (int i = start; i < n && (candidate = candidates[i]) <= target; ++i)
        {
            if (i == start || candidate != candidates[i - 1])
            {
                comb.push_back(candidate);
                dfs(candidates, result, comb, target - candidate, i + 1, n);
                comb.pop_back();
            }
        }
    }
};

class Solution2 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> res;
        map<int, int> count;
        for (int i = 0; i < candidates.size(); ++i)
            ++count[candidates[i]];
        recursiveSum(result, count, res, count.begin(), target);
        return result;
    }
private:
    void recursiveSum(vector<vector<int>>& result, map<int, int>& count, vector<int>& res, map<int, int>::iterator idx, int target) {
        if (target == 0)
        {
            result.push_back(res);
            return;
        }
        for (map<int, int>::iterator it = idx; it != count.end() && it->first <= target; ++it)
        {
            if (it->second == 0)
                continue;
            res.push_back(it->first);
            --it->second;
            recursiveSum(result, count, res, it, target - it->first);
            res.pop_back();  // pop it out before next iteration
            ++it->second;
        }
    }
};