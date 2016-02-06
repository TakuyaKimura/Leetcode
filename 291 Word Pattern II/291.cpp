/*

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, 
such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:
    pattern = "abab", str = "redblueredblue" should return true.
    pattern = "aaaa", str = "asdasdasdasd" should return true.
    pattern = "aabb", str = "xyzabcxzyabc" should return false.

Notes:
You may assume both pattern and str contains only lowercase letters.

*/

#include <string>
#include <algorithm>  // fill_n
#include <unordered_set>
using namespace std;

class Solution2 {
public:
	bool wordPatternMatch(string pattern, string str) {
		unordered_set<string> usedStr;
		string mapping[26];
		fill_n(mapping, 26, "");
		return dfs(pattern, 0, str, 0, usedStr, mapping);
	}
private:
	bool dfs(string& pattern, int i, string& str, int j, unordered_set<string>& usedStr, string(&mapping)[26]) {
		int m = pattern.length(), n = str.length();
		if (i == m || j == n)
			return i == m && j == n;

		int c = pattern[i] - 'a';
		string sub = mapping[c];
		if (!sub.empty())
			return str.substr(j, sub.length()) == sub && dfs(pattern, i + 1, str, j + sub.length(), usedStr, mapping);

		for (int end = j; end + m - i <= n; ++end)
		{
			sub += str[end];  // add one character to the back
			if (usedStr.find(sub) != usedStr.end())
				continue;
			mapping[c] = sub;
			usedStr.insert(sub);
			if (dfs(pattern, i + 1, str, end + 1, usedStr, mapping))
				return true;
			//mapping[c] = "";
			usedStr.erase(sub);
		}
		mapping[c] = "";
		return false;
	}
};

class Solution3 {
public:
	bool wordPatternMatch(string pattern, string str) {
		unordered_set<string> usedStr;
		string mapping[26];
		fill_n(mapping, 26, "");

		int count[26]{ 0 };
		for (char c : pattern)
			++count[c - 'a'];

		return dfs(pattern, 0, str, 0, usedStr, mapping, count, pattern.length());
	}
private:
	bool dfs(string& pattern, int i, string& str, int j, unordered_set<string>& usedStr, string(&mapping)[26], int (&count)[26], int lenToBe) {
		int m = pattern.length(), n = str.length();
		if (lenToBe > n)  // too long, can't fit
			return false;
		if (i == m || j == n)
			return i == m && j == n;

		int c = pattern[i] - 'a';
		string& sub = mapping[c];  // reference type
		if (!sub.empty())
			return str.substr(j, sub.length()) == sub && dfs(pattern, i + 1, str, j + sub.length(), usedStr, mapping, count, lenToBe);

		for (int end = j; end + m - i <= n; ++end)
		{
			sub += str[end];
			if (usedStr.find(sub) != usedStr.end())
				continue;

			usedStr.insert(sub);
													// end - j is the number of additional len for each 'c'
			if (dfs(pattern, i + 1, str, end + 1, usedStr, mapping, count, lenToBe + count[c] * (end - j)))
				return true;

			usedStr.erase(sub);
		}
		sub.clear();
		return false;
	}
};

class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
		unordered_set<string> usedStr;
		string mapping[26];
		fill_n(mapping, 26, "");
		return dfs(pattern, 0, str, 0, usedStr, mapping);
	}
private:
	bool dfs(string& pattern, int i, string& str, int j, unordered_set<string>& usedStr, string(&mapping)[26]) {
		int m = pattern.length(), n = str.length();
		if (i == m && j == n)
			return true;
		if (i == m || j == n)
			return false;

		int c = pattern[i] - 'a';
		string sub = mapping[c];
		if (!sub.empty())
		{
			if (str.substr(j, sub.length()) != sub)
				return false;
			return dfs(pattern, i + 1, str, j + sub.length(), usedStr, mapping);
		}

		// else
		for (int len = 1; len <= n - j - m + i + 1; ++len)
		{
			sub = str.substr(j, len);
			if (usedStr.find(sub) != usedStr.end())  // another char already mapped to this string
				continue;
			mapping[c] = sub;
			usedStr.insert(sub);
			if (dfs(pattern, i + 1, str, j + len, usedStr, mapping))
				return true;
			//mapping[c] = "";
			usedStr.erase(sub);
		}
		mapping[c] = "";
		return false;
    }
};