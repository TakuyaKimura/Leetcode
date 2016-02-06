/*

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
    bool isMatch(const char *s, const char *p)

Some examples:
    isMatch("aa","a") ¡ú false
    isMatch("aa","aa") ¡ú true
    isMatch("aaa","aa") ¡ú false
    isMatch("aa", "*") ¡ú true
    isMatch("aa", "a*") ¡ú true
    isMatch("ab", "?*") ¡ú true
    isMatch("aab", "c*a*b") ¡ú false

*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// DFS back tracking. The pointers save the DFS nodes and back track.
//  O(m*n) in worst cases, consider below input:
// s = "aaaaaaaaaaaaaaaaaaaa"
// p = "*aaaaaaaaaaaaaaaaaab"
// use * to match 0, 1, 2, ... copies of a
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length(), i = 0, j = 0, matched = 0, star = -1;
        while (i < n)
        {
            if (j < m && (p[j] == '?' || s[i] == p[j]))
            {
                ++i;
                ++j;
            }
            else if (j < m && p[j] == '*')
            {
                star = j++;
                matched = i;
            }
            else if (star != -1)
            {
                j = star + 1;  // move back to the position after *, has the same effect as expanding the coverage of *
                i = ++matched;
            }
            else
                return false;
        }
        while (j < m && p[j] == '*')
            ++j;
        return j == m;
    }
};

// DP
class Solution2 {
public:
    bool isMatch(string s, string p) {
        /**
        * f[i][j]: if s[0..i-1] matches p[0..j-1]
        * if p[j - 1] != '*'
        *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
        * if p[j - 1] == '*'
        *      f[i][j] is true iff any of the following is true
        *      1) "*" repeats 0 time and matches empty: f[i][j - 1]
        *      2) "*" repeats >= 1 times and matches "*?": f[i - 1][j] bcoz s[i - 1] matches ? in "*?"
        * '?' matches any single character
        */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

        f[0][0] = true;
        for (int i = 1; i <= m; i++)
            f[i][0] = false;
        // p[0..j - 1] matches empty iff they are all "*"
        for (int j = 1; j <= n; j++)
            f[0][j] = '*' == p[j - 1] && f[0][j - 1];

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
                else
                    f[i][j] = f[i][j - 1] || f[i - 1][j];

        return f[m][n];
    }
};

int main()
{
    string s = "abcbcbd";
    string p = "*bc*bd";
    Solution sol;
    cout << sol.isMatch(s, p);
}