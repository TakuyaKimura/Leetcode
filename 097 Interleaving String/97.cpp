/*

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
    s1 = "aabcc",
    s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

*/

#include <string>
#include <vector>
#include <queue>
using namespace std;

// DP, O(n) space
// use int instead of bool would reduce running time from 8ms to 0ms
class Solution2 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.length(), n2 = s2.length(), n3 = s3.length();
        if (n1 + n2 != n3)
            return false;
        vector<bool> dp(n1 + 1, false);

        // at first, dp[i] is first i chars in s1 with 0 char in s2 forming first i chars in s3
        dp[0] = true;
        for (int i = 0; i < n1 && s3[i] == s1[i]; ++i)  // if one mismatch, the rest are all false
            dp[i + 1] = true;

        for (int i = 0; i < n2; ++i)
        {
            dp[0] = dp[0] && s3[i] == s2[i];
            for (int j = 0; j < n1; ++j)
                dp[j + 1] = dp[j + 1] && s3[i + j + 1] == s2[i] || dp[j] && s3[i + j + 1] == s1[j];
        }

        return dp[n1];
    }
};

// DP, O(m*n space)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.length(), n2 = s2.length(), n3 = s3.length();
        if (n1 + n2 != n3)
            return false;
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        // dp[i][j] = the first i characters of s1 interleaves with the first j characters of s2
        //            forming the first (i+j) characters of s3

        dp[0][0] = true;
        for (int i = 0; i < n1 && s3[i] == s1[i]; ++i)  // if one mismatch, the rest are all false
            dp[i + 1][0] = true;
        for (int j = 0; j < n2 && s3[j] == s2[j]; ++j)
            dp[0][j + 1] = true;

        for (int i = 1; i <= n1; ++i)
            for (int j = 1; j <= n2; ++j)
                dp[i][j] = s3[i + j - 1] == s1[i - 1] && dp[i - 1][j] || s3[i + j - 1] == s2[j - 1] && dp[i][j - 1];

        return dp[n1][n2];
    }
};

// BFS
// If we expand the two strings s1 and s2 into a chessboard, then this problem can be transferred into
// a path seeking problem from the top-left corner to the bottom-right corner
class Solution3 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n1 = s1.length(), n2 = s2.length(), n3 = s3.length(), k = 0;
        if (n1 + n2 != n3)
            return false;
        vector<vector<bool>> visited(n1 + 1, vector<bool>(n2 + 1, false));
        visited[0][0] = true;  // if n1 == n2 == 0, it's true
        queue<pair<int, int>> q;  // (i, j) the next char we're gonna check are s1[i] and s2[j]
        q.push(make_pair(0, 0));
        while (!q.empty())
        {
            int size = q.size();
            char c = s3[k++];
            while (size--)
            {
                int i = q.front().first, j = q.front().second;
                q.pop();
                if (i < n1 && s1[i] == c && !visited[i + 1][j])
                {
                    q.push(make_pair(i + 1, j));
                    visited[i + 1][j] = true;
                }
                if (j < n2 && s2[j] == c && !visited[i][j + 1])
                {
                    q.push(make_pair(i, j + 1));
                    visited[i][j + 1] = true;
                }
                if (visited[n1][n2])  // whenever we found one, return early
                    return true;
            }
        }
        return false;
    }
};