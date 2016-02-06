/*

Given a string containing just the characters '(' and ')', 
find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

*/

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length(), longest = 0;
        vector<int> dp(n + 1, 0);  // dp[i] = longest ending at the ith character s[i-1]

        for (int i = 0; i < n; ++i)
        {
            int j = i - dp[i] - 1;
            if (s[i] == ')' && j >= 0 && s[j] == '(')
            {
                dp[i + 1] = dp[i] + 2 + dp[j];        // ending at s[j-1]
                longest = max(longest, dp[i + 1]);
            }
        }
        return longest;
    }
};