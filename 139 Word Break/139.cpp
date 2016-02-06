/*

Given a string s and a dictionary of words dict, 
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
    s = "leetcode",
    dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

*/

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_set>
using namespace std;

// time complexity:
//   1 + (1 + 2) + (1 + 2 + 3) + ... + (1 + 2 + ... + n)
// = 1/2 * [(1^2 + 1) + (2^2 + 2) + ... + (n^2 + n)]
// = 1/2 * [(1^2 + 2^2 + ... + n^2) + (1 + 2 + ... + n)]
// = 1/2 * (n(n+1)(2n+1)/6 + n(n+1)/2)
// = O(n^3)

// DP, 4ms
// optimization: look from the smaller substring, s.substr() will take less time
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.length(), i, j;
        vector<bool> dp(n + 1, false);  // dp[i] = whether the first i characters can be segmented
        dp[0] = true;
        for (i = 1; i <= n; ++i)
            //for (j = 0; j < i; ++j)
            for (j = i - 1; j >= 0; --j)  // this will reduce the runtime from 12ms to 4ms, because the smaller the substring is, the faster
                if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end())
                {
                    dp[i] = true;
                    break;
                }
        return dp[n];
    }
};

// DP, 0ms
// optimization: find out the valid length of words (or even with just maxlen)
class Solution2 {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.length(), i, j, len, minlen = INT_MAX, maxlen = 0;
        for (auto& word : wordDict)
        {
            len = word.length();
            minlen = min(minlen, len);
            maxlen = max(maxlen, len);
        }
        vector<bool> dp(n + 1, false);  // dp[i] = whether the first i characters can be segmented
        dp[0] = true;
        for (i = 1; i <= n; ++i)
            //for (j = 0; j < i; ++j)
            for (j = i - minlen; j >= max(0, i - maxlen); --j)
                if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end())
                {
                    dp[i] = true;
                    break;
                }
        return dp[n];
    }
};

// BFS using queue, with the start index as node, 4ms
class Solution3 {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        queue<int> q;
        int n = s.length(), start, i, len, minlen = INT_MAX, maxlen = 0;
        for (auto& word : wordDict)
        {
            len = word.length();
            minlen = min(minlen, len);
            maxlen = max(maxlen, len);
        }
        vector<bool> visited(n + 1, false);
        q.push(0);
        visited[0] = true;
        while (!q.empty())
        {
            start = q.front();
            q.pop();
            for (i = start + minlen; i <= min(n, start + maxlen); ++i)
                if (!visited[i] && wordDict.find(s.substr(start, i - start)) != wordDict.end())
                {
                    if (i == n)
                        return true;
                    q.push(i);
                    visited[i] = true;
                }
        }
        return false;
    }
};

// DFS using stack, 4ms
class Solution4 {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        stack<int> q;
        int n = s.length(), start, i, len, minlen = INT_MAX, maxlen = 0;
        for (auto& word : wordDict)
        {
            len = word.length();
            minlen = min(minlen, len);
            maxlen = max(maxlen, len);
        }
        vector<bool> visited(n + 1, false);
        q.push(0);
        visited[0] = true;
        while (!q.empty())
        {
            start = q.top();
            q.pop();
            for (i = start + minlen; i <= min(n, start + maxlen); ++i)
                if (!visited[i] && wordDict.find(s.substr(start, i - start)) != wordDict.end())
                {
                    if (i == n)
                        return true;
                    q.push(i);
                    visited[i] = true;
                }
        }
        return false;
    }
};