/*

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:
    [
        [2,4],
        [3,4],
        [2,3],
        [1,2],
        [1,3],
        [1,4],
    ]

*/

#include <vector>
using namespace std;

// running time:
// fill in one position at a time
// n choose k combinations, k positions each
// O(n) = k * C(n,k) = k * n! / k!(n-k)!
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> comb(k);
        fillIn(result, comb, n, k);
        return result;
    }
private:
    // fill in the first k positions using the first n numbers
    void fillIn(vector<vector<int>>& result, vector<int>& comb, int n, int k) {
        if (k == 0)
        {
            result.push_back(comb);
            return;
        }
        for (int i = n; i >= k; --i)
        {
            comb[k - 1] = i;  // start from the back
            fillIn(result, comb, i - 1, k - 1);  // note it's i - 1, not n - 1
        }
    }
};

// iterative
// 1,2,3,...,k-1,k
// 1,2,3,...,k-1,k+1
// ...
// 1,2,3,...,k-1,n
// 1,2,3,...,k,k+1
// 1,2,3,...,k,k+2
// ...
// 1,2,3,...,k,n
// 1,2,3,...,k+1,k+2
// ...
// 1,2,3,...,n-1,n
// ...
// n-k+1,n-k+2,...,n
class Solution2 {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> comb(k, 0);
        int idx = 0, max0 = n - k + 1;  // max number for comb[0]
        while (idx >= 0)
        {
            ++comb[idx];
            if (comb[idx] > max0 + idx)
                --idx;
            else if (idx == k - 1)
                result.push_back(comb);
            else
            {
                comb[idx + 1] = comb[idx];
                ++idx;
            }
        }
        return result;
    }
};