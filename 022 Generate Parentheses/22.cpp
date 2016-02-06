/*

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"

*/

#include <vector>
#include <string>
using namespace std;

// DP
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> dp(n + 1);
        dp[0].push_back("");
        // all strings start with '(', find its closing ')'
        // it must be in the form ( s1 ) s2
        // so we just need to determine what to put in the first pair of paren
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                for (string& in : dp[j])
                    for (string& out : dp[i - j - 1])
                        dp[i].push_back("(" + in + ")" + out);
        return dp[n];
    }
};

// recursion, dfs
class Solution2 {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        putParen(result, "", n, 0);
        return result;
    }
private:
    // we can either put a left or right paren
    // if we put a left, next iteration has one less left, one more right to put
    // if we put a right, next iteration has one less right to put
    void putParen(vector<string>& result, string str, int left, int right) {
        if (left == 0 && right == 0)
            result.push_back(str);
        if (left > 0)
            putParen(result, str + '(', left - 1, right + 1);  // note: right + 1
        if (right > 0)
            putParen(result, str + ')', left, right - 1);
    }
};

// recursion, dfs
class Solution3 {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        putParen(result, "", n, n);
        return result;
    }
private:
    void putParen(vector<string>& result, string str, int left, int right) {
        if (left)
            putParen(result, str + '(', left - 1, right);
        if (right > left)
            putParen(result, str + ')', left, right - 1);
        if (!right)  // there is no possible way that left > right, it's always left <= right
            result.push_back(str);
    }
};