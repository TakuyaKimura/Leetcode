/*

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string 
by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. 
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.

*/

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// what should be returned when t is empty?
class Solution2 {
public:
    int numDistinct(string s, string t) {
        int tlen = t.length();
        vector<int> dp(tlen + 1, 0);  // dp[i] - ways to match the first i chars in t
        dp[0] = 1;
        for (char c : s)
            for (int i = tlen - 1; i >= 0; --i)  // update from the large index (if from the small, need to store the value in a temp variable)
                if (c == t[i])
                    dp[i + 1] += dp[i];
        return dp[tlen];
    }
};

// store the locations to minimize array access
// otherwise for each char is s, we have to access all the chars in t
class Solution3 {
public:
    int numDistinct(string s, string t) {
        int slen = s.length(), tlen = t.length();
        unordered_map<char, vector<int>> loc;

        for (int i = 0; i < tlen; ++i)
            loc[t[i]].push_back(i);

        vector<int> num(tlen + 1, 0);
        num[0] = 1;
        vector<int> indices;

        for (char c : s)
        {
            if (loc.find(c) == loc.end())
                continue;

            indices = loc[c];
            /* update from larger indices to smaller indices */
            for (int i = indices.size() - 1; i >= 0; --i)
                num[indices[i] + 1] += num[indices[i]];
        }

        return num[tlen];
    }
};

class Solution {
public:
    int numDistinct(string S, string T) {
        int s = S.length(), t = T.length();
        if (s < t)
            return 0;
        vector<vector<int>> A(s + 1, vector<int>(t + 1));
        for (int i = 0; i <= s; i++)  // any string-->delete some characters-->empty string, unique way
            A[i][0] = 1;
        for (int j = 1; j <= t; j++)  // empty string can't become a nonempty string
            A[0][j] = 0;
        for (int i = 1; i <= s; i++)
            for (int j = 1; j <= t; j++)
                if (S[i - 1] == T[j - 1])  // ith character and jth character
                    A[i][j] = A[i - 1][j - 1] + A[i - 1][j];
        // match S[i] and T[j], or don't match
                else
                    A[i][j] = A[i - 1][j];
        return A[s][t];
    }
};