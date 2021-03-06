/*

Numbers can be regarded as product of its factors. For example,

    8 = 2 x 2 x 2;
      = 2 x 4.

Write a function that takes an integer n and return all possible combinations of its factors.

Note:
Each combination's factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].

You may assume that n is always positive.

Factors should be greater than 1 and less than n.

Examples:
input: 1
output:
    []

input: 37
output:
    []

input: 12
output:
    [
        [2, 6],
        [2, 2, 3],
        [3, 4]
    ]

input: 32
output:
    [
        [2, 16],
        [2, 2, 8],
        [2, 2, 2, 4],
        [2, 2, 2, 2, 2],
        [2, 4, 4],
        [4, 8]
    ]

*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> result;
        vector<int> factors{ n };
        dfs(2, factors, result);
        return result;
    }
private:
    void dfs(int smallest, vector<int>& factors, vector<vector<int>>& result) {
        int n = factors.back();
        factors.pop_back();
        for (int i = smallest; i <= n / i; ++i)
            if (n % i == 0)
            {
                factors.push_back(i);
                factors.push_back(n / i);
                result.push_back(factors);
                dfs(i, factors, result);
                factors.pop_back();
            }
    }
};