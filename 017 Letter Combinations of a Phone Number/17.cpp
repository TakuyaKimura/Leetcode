/*

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

*/

#include <string>
#include <vector>
using namespace std;

// similar to Problem 46 Permutations

// BFS, all intermediate strings have the same length
class Solution3 {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty())
            return result;
        result.push_back("");
        string mapping[] { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (auto digit : digits)
        {
            vector<string> tempVec;
            for (auto &str : result)
                for (auto c : mapping[digit - '0'])
                    tempVec.push_back(str + c);
            result = tempVec;
        }
        return result;
    }
};

// BFS
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> pre{ "" };
        vector<string> cur;
        if (digits.empty())
            return cur;
        string mapping[] { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        for (char digit : digits)
        {
            for (char c : mapping[digit - '0'])
                for (string& s : pre)
                    cur.push_back(s + c);
            pre = cur;
            cur.clear();
        }
        return pre;
    }
};

// DFS
class Solution5 {
public:
    vector<string> letterCombinations(string digits) {
        // can't declare as global variable
        vector<string> mapping{ "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        vector<string> result;
        int n = digits.length();
        string str(n, '\0');
        if (n)
            dfs(digits, n, 0, result, str, mapping);
        return result;
    }
private:
    void dfs(string& digits, int n, int idx, vector<string>& result, string str, vector<string>& mapping) {
        if (idx == n)
        {
            result.push_back(str);
            return;
        }
        for (char c : mapping[digits[idx] - '0'])
        {
            str[idx] = c;
            dfs(digits, n, idx + 1, result, str, mapping);
        }
    }
};

// DFS
class Solution2 {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        int n = digits.length();
        if (n == 0)
            return result;
        string str;
        int convert[9] { 0, 3, 6, 9, 12, 15, 19, 22, 26 };
        dfs(result, str, digits, 0, n, convert);
        return result;
    }
private:
    void dfs(vector<string> &result, string str, string &digits, int idx, int n, int* convert) {
        if (idx == n)
        {
            result.push_back(str);
            return;
        }
        int tmp = digits[idx] - '2';  //change '2' to 0, '3' to 1...
        for (int i = convert[tmp]; i < convert[tmp + 1]; ++i)
        {
            str.push_back('a' + i);  //ex: a,b,c | d,e,f
            dfs(result, str, digits, idx + 1, n, convert);
            str.pop_back();
        }
    }
};

// Imagine a string to be a large number with heterogenous base for each position
// then just enumerate all of it, and do base conversion
class Solution4 {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> dict { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        vector<string> ans;
        size_t total = 1, n = digits.size(), p, i, j;
        if (n == 0)
            return ans;
        string s;
        int idx, base, v;
        for (auto c : digits)
            total *= dict[c - '0'].length();
        for (i = 0; i < total; ++i)
        {
            p = i;
            s = "";
            for (auto c : digits)
            {
                idx = c - '0';
                base = dict[idx].length();
                v = p % base;
                s += dict[idx][v];
                p /= base;
            }
            ans.push_back(s);
        }
        return ans;
    }
};