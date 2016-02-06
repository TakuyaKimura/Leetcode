/*

Remove the minimum number of invalid parentheses in order to make the input string valid. 

Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Examples:
    "()())()" -> ["()()()", "(())()"]
    "(a)())()" -> ["(a)()()", "(a())()"]
    ")(" -> [""]

*/

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

// BFS, naive implementation, 136ms
// T(n) = n x C(n, n) + (n-1) x C(n, n-1) + ... + 1 x C(n, 1) = n x 2^(n-1)
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> q;
        vector<string> result;
        if (isValid(s))
        {
            result.push_back(s);
            return result;
        }
        q.push(s);
        bool found = false;
        int n = s.length(), size;
        char c;
        while (!q.empty())
        {
            unordered_set<string> visited;
            size = q.size();
            while (size--)
            {
                s = q.front();
                q.pop();
                for (int i = 0; i < n; ++i)
                {
                    c = s[i];
                    if (c == '(' || c == ')')
                    {
                        s.erase(i, 1);
                        if (visited.find(s) == visited.end())
                        {
                            visited.insert(s);

                            if (isValid(s))
                            {
                                result.push_back(s);
                                found = true;
                            }
                            if (!found)
                                q.push(s);  // when all parentheses are removed, it will always be valid, so the queue is eventually empty
                        }
                        s.insert(i, 1, c);
                    }
                }
            }
            --n;  // length of all the strings in the queue
        }
        return result;
    }
private:
    bool isValid(string s) {
        int left = 0;
        for (char c : s)
            if (c == '(')
                ++left;
            else if (c == ')')
            {
                if (left == 0)
                    return false;
                --left;
            }
        return !left;
    }
};

// BFS, optimization1: always remember the last position where we delete character, next deletion only after. 68ms
class Solution2 {
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<pair<string, int>> q;
        vector<string> result;
        if (isValid(s))
        {
            result.push_back(s);
            return result;
        }
        q.push(make_pair(s, 0));
        bool found = false;
        int n = s.length(), size, start;
        char c;
        while (!q.empty())
        {
            unordered_set<string> hash;
            size = q.size();
            while (size--)
            {
                s = q.front().first;
                start = q.front().second;
                q.pop();
                for (int i = start; i < n; ++i)
                {
                    c = s[i];
                    if (c == '(' || c == ')')
                    {
                        s.erase(i, 1);
                        if (hash.find(s) == hash.end())
                        {
                            hash.insert(s);

                            if (isValid(s))
                            {
                                result.push_back(s);
                                found = true;
                            }
                            if (!found)
                                q.push(make_pair(s, i));  // when all parentheses are removed, it will always be valid, so the queue is eventually empty
                        }
                        s.insert(i, 1, c);
                    }
                }
            }
            --n;  // length of all the strings in the queue
        }
        return result;
    }
private:
    bool isValid(string s) {
        int left = 0;
        for (char c : s)
            if (c == '(')
                ++left;
            else if (c == ')')
            {
                if (left == 0)
                    return false;
                --left;
            }
        return !left;
    }
};

// BFS, optimization2: when there are consecutive '('s or ')'s, only delete the first one
// with the above two optimizations, we will avoid generating duplicate strings, so don't need hash
// 36ms
class Solution3 {
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<pair<string, int>> q;
        vector<string> result;
        if (isValid(s))
        {
            result.push_back(s);
            return result;
        }
        q.push(make_pair(s, 0));
        bool found = false;
        int n = s.length(), size, start;
        char c;
        while (!q.empty())
        {
            size = q.size();
            while (size--)
            {
                s = q.front().first;
                start = q.front().second;
                q.pop();
                for (int i = start; i < n; ++i)
                {
                    c = s[i];
                    if ((c == '(' || c == ')') && (i == start || c != s[i - 1]))
                    {
                        s.erase(i, 1);

                        if (isValid(s))
                        {
                            result.push_back(s);
                            found = true;
                        }
                        if (!found)
                            q.push(make_pair(s, i));  // when all parentheses are removed, it will always be valid, so the queue is eventually empty
                        
                        s.insert(i, 1, c);
                    }
                }
            }
            --n;  // length of all the strings in the queue
        }
        return result;
    }
private:
    bool isValid(string s) {
        int left = 0;
        for (char c : s)
            if (c == '(')
                ++left;
            else if (c == ')')
            {
                if (left == 0)
                    return false;
                --left;
            }
        return !left;
    }
};

// DFS, find out first how many characters need to be removed. 8ms
class Solution4 {
public:
    vector<string> removeInvalidParentheses(string s) {
        int target = needRemove(s);
        vector<string> result;
        dfs(result, s, target, 0);
        return result;
    }

private:
    void dfs(vector<string>& result, string& s, int target, int idx) {
        if (target == 0)
        {
            if (isValid(s))
                result.push_back(s);
            return;
        }
        char c;
        int n = s.length();
        for (int i = idx; i <= n - target; ++i)  // whether enough characters left
        {
            c = s[i];
            if ((c == '(' || c == ')') && (i == idx || c != s[i - 1]))
            {
                s.erase(i, 1);
                dfs(result, s, target - 1, i);
                s.insert(i, 1, c);
            }
        }
    }

    int needRemove(string& s) {
        int result = 0, left = 0;
        for (char c : s)
            if (c == '(')
            {
                ++left;
                ++result;
            }
            else if (c == ')')
                if (left)
                {
                    --left;
                    --result;
                }
                else
                    ++result;
        return result;
    }

    bool isValid(string& s) {
        int left = 0;
        for (char c : s)
            if (c == '(')
                ++left;
            else if (c == ')')
            {
                if (left == 0)
                    return false;
                --left;
            }
        return !left;
    }
};

// DFS, further optimize: if last round removed a '(', then this round shouldn't remove a ')'. 4ms
class Solution4 {
public:
    vector<string> removeInvalidParentheses(string s) {
        int target = needRemove(s);
        vector<string> result;
        dfs(result, s, target, 0, ' ');
        return result;
    }

private:
    void dfs(vector<string>& result, string& s, int target, int idx, char justRemoved) {
        if (target == 0)
        {
            if (isValid(s))
                result.push_back(s);
            return;
        }
        char c;
        int n = s.length();
        for (int i = idx; i <= n - target; ++i)  // whether enough characters left
        {
            c = s[i];
            if (c != '(' && c != ')' || c == ')' && justRemoved == '(')
                continue;
            if (i == idx || c != s[i - 1])
            {
                s.erase(i, 1);
                dfs(result, s, target - 1, i, c);
                s.insert(i, 1, c);
            }
        }
    }

    int needRemove(string& s) {
        int result = 0, left = 0;
        for (char c : s)
            if (c == '(')
            {
                ++left;
                ++result;
            }
            else if (c == ')')
                if (left)
                {
                    --left;
                    --result;
                }
                else
                    ++result;
        return result;
    }

    bool isValid(string& s) {
        int left = 0;
        for (char c : s)
            if (c == '(')
                ++left;
            else if (c == ')')
            {
                if (left == 0)
                    return false;
                --left;
            }
        return !left;
    }
};

// https://leetcode.com/discuss/67954/solution-generating-only-longest-valid-strings-using-hash
// 0ms
class Solution5 {
public:
    vector<string> removeInvalidParentheses(string s) {
        maxAnsLen = 0;
        strLen = s.size();
        cnt = 0;
        str = s;
        tmp = "";

        numAntiP = new int[strLen + 1];
        jump = new int[strLen + 1];
        numAntiP[strLen] = 0;
        jump[strLen] = strLen;
        str.push_back('@');
        for (int i = strLen - 1; i >= 0; --i)
        {
            numAntiP[i] = numAntiP[i + 1] + (str[i] == ')');
            if (str[i] == ')')
                jump[i] = (str[i + 1] == ')') ? jump[i + 1] : (i + 1);
            if (str[i] == '(')
                jump[i] = (str[i + 1] == '(') ? jump[i + 1] : (i + 1);
        }

        dfs(0);
        return ans;
    }
private:
    int cnt, *numAntiP, *jump, strLen, maxAnsLen;
    vector<string> ans;
    string str, tmp;

    void dfs(int i) {
        if (strLen - i + tmp.size() < maxAnsLen)
            return;
        else if (i == strLen)
        {
            maxAnsLen = tmp.size();
            ans.push_back(tmp);
        }
        else if (str[i] == ')')
        {
            if (cnt > 0)
            {
                --cnt;
                tmp.push_back(str[i]);
                dfs(i + 1);
                tmp.pop_back();
                ++cnt;
            }
            if (numAntiP[i + 1] >= cnt)
                dfs(jump[i]);
        }
        else if (str[i] == '(')
        {
            if (numAntiP[i + 1] > cnt)
            {
                ++cnt;
                tmp.push_back(str[i]);
                dfs(i + 1);
                tmp.pop_back();
                --cnt;
            }
            dfs(jump[i]);
        }
        else
        {
            tmp.push_back(str[i]);
            dfs(i + 1);
            tmp.pop_back();
        }
    }
};