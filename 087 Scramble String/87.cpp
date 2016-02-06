/*

Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

        great
        /    \
       gr    eat
      / \    /  \
     g   r  e   at
                / \
               a   t

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

            rgeat
           /    \
          rg    eat
         / \    /  \
        r   g  e   at
                   / \
                  a   t

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

            rgtae
           /    \
          rg    tae
         / \    /  \
        r   g  ta  e
               / \
              t   a

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

*/

#include <string>
#include <vector>
using namespace std;

// recursion
class Solution2 {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.length();  // s1 and s2 are of the same length
        if (s1 == s2)  // base case
            return true;
        int count[128] { 0 };
        for (int i = 0; i < n; ++i)
        {
            ++count[s1[i]];
            --count[s2[i]];
        }
        for (int c : count)
            if (c)
                return false;
        for (int len = 1; len < n; ++len)
            if (isScramble(s1.substr(0, len), s2.substr(0, len)) && isScramble(s1.substr(len), s2.substr(len)) ||
                isScramble(s1.substr(0, len), s2.substr(n - len)) && isScramble(s1.substr(len), s2.substr(0, n - len)))
                return true;
        return false;
    }
};

// DP
class Solution {
public:
    bool isScramble(string s1, string s2) {
        const int n = s1.length();  // s1 and s2 are of the same length
        bool ***dp = new bool **[n];
        // vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n, false)));
        // vector is too slow

        // dp[i][j][k] = is s1[i...i+k] a scramble of s2[j...j+k]

        for (int i = 0; i < n; ++i)
        {
            dp[i] = new bool *[n];
            for (int j = 0; j < n; ++j)
            {
                dp[i][j] = new bool[n];
                dp[i][j][0] = (s1[i] == s2[j]);
            }
        }
        // s1's left substring scrambles s2's left substring, and s1's right substring scrambles s2's right substring
        // or s1's left substring scrambles s2's right substring, and s1's right substring scrambles s2's left substring
        for (int k = 1; k < n; ++k)
            for (int i = 0; i < n - k; ++i)
                for (int j = 0; j < n - k; ++j)
                    for (int m = 0; m < k; ++m)
                        if (dp[i][j][k] = dp[i][j][m] && dp[i + m + 1][j + m + 1][k - m - 1] || dp[i][j + k - m][m] && dp[i + m + 1][j][k - m - 1])
                            break;
        bool result = dp[0][0][n - 1];

//--------- remember to delete ------------------------------------------------------
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                delete[] dp[i][j];
            delete[] dp[i];
        }
        delete dp;
//-----------------------------------------------------------------------------------
        return result;
    }
};