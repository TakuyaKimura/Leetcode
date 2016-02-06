/*

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

    [
        ["aa","b"],
        ["a","a","b"]
    ]

*/

#include <vector>
#include <string>
using namespace std;

// DFS + backtracking + DP, keep record of if substrings are palindrome (kinda like DP), 12ms
// use 2-dimensional vector would increase to 16ms
class Solution3 {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> result;
        vector<string> sol;
        vector<bool> dp(n * n, false);  // dp[i * n + j] for s[i..j]
        dp[0] = true;
        for (int i = 1; i < n; ++i)
        {
            dp[i * n + i] = true;
            if (s[i] == s[i - 1])
                dp[(i - 1) * n + i] = true;
        }
        for (int gap = 2; gap < n; ++gap)
            for (int i = 0; i + gap < n; ++i)
                if (s[i] == s[i + gap] && dp[(i + 1) * n + i + gap - 1])  // all values for gap-1 are already calculated
                    dp[i * n + i + gap] = true;

        dfs(s, dp, n, 0, sol, result);
        return result;
    }
private:
    void dfs(string& s, vector<bool>& dp, int n, int start, vector<string>& sol, vector<vector<string>>& result)
    {
        if (start == n)
            result.push_back(sol);

        for (int i = start; i < n; ++i)
            if (dp[start * n + i])
            {
                sol.push_back(s.substr(start, i - start + 1));
                dfs(s, dp, n, i + 1, sol, result);
                sol.pop_back();
            }
    }
};

// DFS, backtracking, 12ms
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> sol;
        getPartition(s, s.length(), 0, sol, result);
        return result;
    }
private:
    void getPartition(string& s, int n, int start, vector<string>& sol, vector<vector<string>>& result) {
        if (start == n)
            result.push_back(sol);

        for (int i = start; i < n; i++)
        {
            int l = start, r = i;
            bool isPalindrome = true;
            while (l < r)
                if (s[l++] != s[r--])
                {
                    isPalindrome = false;
                    break;
                }

            if (isPalindrome)
            {
                sol.push_back(s.substr(start, i - start + 1));
                getPartition(s, n, i + 1, sol, result);
                sol.pop_back();
            }
        }
    }
};

// DP, 32ms (use int instead of bool would reduce to 28ms), calculate the result for each prefix
// worst case O(2^n): aaa...aaa
// between each two chars, whether to break
class Solution2 {
public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<string> temp;
        vector<vector<vector<string>>> result(n + 1);  // result[i] for the first i characters
        result[0].push_back(vector<string>());
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));  // palindrome[i][j] - substring [i..j]
        for (int i = 0; i < n; ++i)
        {
            char c = s[i];
            for (int j = 0; j <= i; ++j)
            {
                if (j == i)
                    palindrome[j][i] = true;
                else
                {
                    if (s[j] != c)
                        continue;
                    if (j == i - 1 || palindrome[j + 1][i - 1])  // all values for i-1 are already calculated
                        palindrome[j][i] = true;
                }
                if (palindrome[j][i])
                {
                    string str = s.substr(j, i - j + 1);
                    for (auto& v : result[j])  // first j - 1 chars
                    {
                        temp = v;
                        temp.push_back(str);
                        result[i + 1].push_back(temp);  // first i chars
                    }
                }
            }
        }
        return result[n];
    }
};