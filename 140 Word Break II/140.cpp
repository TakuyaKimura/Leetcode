/*

Given a string s and a dictionary of words dict, 
add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
    s = "catsanddog",
    dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

*/

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// DP + DFS
class Solution3 {
public:
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
		int n = s.length(), minLen = INT_MAX, maxLen = INT_MIN;
		for (auto& word : wordDict)
		{
			int len = word.length();
			minLen = min(minLen, len);
			maxLen = max(maxLen, len);
		}

		vector<vector<int>> startingIdx(n + 1);
		for (int end = minLen; end <= n; ++end)  // end is the right end + 1
			for (int start = end - minLen; start >= 0 && start >= end - maxLen; --start)
			{
				// so we don't need backtracking, all entries are useful to construct the path
				if (start != 0 && startingIdx[start].empty() || wordDict.find(s.substr(start, end - start)) == wordDict.end())
					continue;
				startingIdx[end].push_back(start);
			}

		vector<string> result;
		dfs(startingIdx, result, s, "", n);
		return result;
	}

private:
	void dfs(vector<vector<int>>& startingIdx, vector<string>& result, string& s, string breaking, int end) {
		if (end == 0)
		{
			if (!breaking.empty())
				breaking.pop_back();  // remove the trailing space
			result.push_back(breaking);
			return;
		}
		for (int start : startingIdx[end])
		{
			string str = s.substr(start, end - start) + ' ' + breaking;
			dfs(startingIdx, result, s, str, start);
		}
	}
};

// 8ms, DFS
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int n = s.length();
        vector<vector<int>> ending_idx(n);
        for (int end = n; end >= 0; --end)  // end is the right end + 1
        {
            if (end < n && ending_idx[end].empty())  // there's no word starts from here
                continue;
            for (int start = end - 1; start >= 0; --start)
                if (wordDict.find(s.substr(start, end - start)) != wordDict.end())
                    ending_idx[start].push_back(end);
        }
        vector<string> result;
        collect(ending_idx, 0, s, "", result);
        return result;
    }
private:
    void collect(vector<vector<int>>& ending_idx, int start, const string& s, string path, vector<string>& result)
    {
        for (auto& end : ending_idx[start])
        {
            string sub = s.substr(start, end - start);
            string newpath = path + (start == 0 ? sub : " " + sub);
            if (end == s.length())
                result.push_back(newpath);
            else
                collect(ending_idx, end, s, newpath, result);
        }
    }
};

// 4ms, DFS + DP
class Solution2 {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> res;
        if (!canWordBreak(s, wordDict))
            return res;
        string str;
        wordBreakHelper(s, wordDict, 0, str, res);
        return res;
    }

private:
    int len, min_len, max_len;

    // determine if s can be segmented and calculate the effective length of the substring.
    bool canWordBreak(string& s, unordered_set<string>& wordDict) {
        if (wordDict.empty())
            return false;
        len = s.size(), min_len = max_len = wordDict.begin()->size();
        int temp;
        for (auto& word : wordDict)
        {
            temp = word.size();
            if (temp > max_len)
                max_len = temp;
            else if (temp < min_len)
                min_len = temp;
        }

        vector<bool> flag(len + 1);
        flag[len] = true;
        for (int i = len - 1; i >= 0; --i)
            for (int j = min_len; j <= min(max_len, len - i); ++j)
                if (flag[i + j] && wordDict.find(s.substr(i, j)) != wordDict.end())
                {
                    flag[i] = true;
                    break;
                }

        return flag[0];
    }

    void wordBreakHelper(string& s, unordered_set<string>& wordDict, int begin, string& str, vector<string>& res) {
        for (int i = min_len; i <= min(max_len, len - begin); ++i)
            if (wordDict.find(s.substr(begin, i)) != wordDict.end())
                if (i == len - begin)
                    res.push_back(str + s.substr(begin, i));
                else
                {
                    string pre = str;
                    str += s.substr(begin, i) + " ";
                    wordBreakHelper(s, wordDict, begin + i, str, res);
                    str = pre;
                }
    }
};