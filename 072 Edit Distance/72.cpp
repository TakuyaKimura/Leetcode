/*

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
(each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

    a) Insert a character
    b) Delete a character
    c) Replace a character

*/

#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // dp[i][j] = steps for the first i characters of word1 and first j characters of word2
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i)
            dp[i][0] = i;
        for (int j = 1; j <= n; ++j)
            dp[0][j] = j;
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (word1[i - 1] == word2[j - 1])  // ith character and jth character
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
        return dp[m][n];
    }
};

// can reduce the space to two vectors
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<int> pre(n + 1), cur(n + 1);

        for (int j = 0; j <= n; ++j)
            pre[j] = j;

        for (int i = 1; i <= m; ++i)
        {
            cur[0] = i;
            for (int j = 1; j <= n; ++j)
                if (word1[i - 1] == word2[j - 1])  // ith character and jth character
                    cur[j] = pre[j - 1];
                else
                    cur[j] = min(min(pre[j - 1], pre[j]), cur[j - 1]) + 1;
            pre = cur;
        }

        return pre[n];
    }
};

// can further reduce the space to one vector
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length(), pre, temp;
        vector<int> cur(n + 1);

        for (int j = 0; j <= n; ++j)
            cur[j] = j;

        for (int i = 1; i <= m; ++i)
        {
            pre = cur[0];
            cur[0] = i;
            for (int j = 1; j <= n; ++j)
            {
                temp = cur[j];
                if (word1[i - 1] == word2[j - 1])  // ith character and jth character
                    cur[j] = pre;
                else
                    cur[j] = min(min(pre, cur[j]), cur[j - 1]) + 1;
                pre = temp;
            }
        }

        return cur[n];
    }
};