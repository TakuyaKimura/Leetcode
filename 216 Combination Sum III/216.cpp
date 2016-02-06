/*

Find all possible combinations of k numbers that add up to a number n, 
given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Ensure that numbers within the set are sorted in ascending order.

Example 1:

    Input: k = 3, n = 7

    Output: [[1,2,4]]

Example 2:

    Input: k = 3, n = 9

    Output: [[1,2,6], [1,3,5], [2,3,4]]

*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> comb;
        dfs(result, comb, k, n, 1);
        return result;
    }
private:
    void dfs(vector<vector<int>>& result, vector<int>& comb, int k, int n, int start) {
        if (k == 0 && n == 0)
            result.push_back(comb);
        if (k == 0 || n < start * k)
            return;
        for (int i = start; i < 10; ++i)
        {
            comb.push_back(i);
            dfs(result, comb, k - 1, n - i, i + 1);
            comb.pop_back();
        }
    }
};

// iterative, adapted from Problem 77
class Solution2 {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> comb(k, 0);
        int idx = 0, sum = 0;
        while (idx >= 0)
        {
            ++comb[idx];
            ++sum;
            if (comb[idx] + k - idx > 10 || sum > n)
            {
                sum -= comb[idx];
                --idx;
            }
            else if (idx == k - 1)
            {
                if (sum == n)
                    result.push_back(comb);
            }
            else
            {
                comb[idx + 1] = comb[idx];
                sum += comb[idx];
                ++idx;
            }
        }
        return result;
    }
};