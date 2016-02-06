/*

Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = "eceba",

T is "ece" which its length is 3.

*/

#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

// two-pass but still fast, can extend to k
class Solution2 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		int count[256] = { 0 }, n = s.length(), used = 0, len = 0, start = 0;
		for (int i = 0; i < n; ++i)
		{
			char c = s[i];
			if (count[c] == 0 && used == 2)
			{
				len = max(len, i - start);
				while (--count[s[start++]]) {}
			}
			else if (count[c] == 0)
				++used;

			++count[c];
		}
		return max(len, n - start);
	}
};

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
		int n = s.length(), left = 0, firstEnd = -1, len = 0;
		for (int i = 1; i < n; ++i)
		{
			if (s[i] == s[i - 1])  // s[i - 1] must be the second ending char
				continue;
			if (firstEnd >= 0 && s[i] != s[firstEnd])  // third char is coming
			{
				len = max(len, i - left);
				left = firstEnd + 1;
			}
			firstEnd = i - 1;
		}
		return max(len, n - left);
    }
};

// slower, can extend to k
class Solution3 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		int n = s.length(), i = 0, maxLen = 0;
		unordered_map<char, int> used;  // the last position of c currently in the window
		for (int j = 0; j < n; ++j)
		{
			char c = s[j];

			if (used.size() < 2 || used.find(c) != used.end())
				used[c] = j;
			else
			{
				maxLen = max(maxLen, j - i);

				for (auto it = used.begin(); it != used.end(); ++it)
					if (it->first != s[j - 1])
					{
						i = it->second + 1;
						used.erase(it);
						break;
					}

				used[c] = j;
			}
		}
		return max(maxLen, n - i);
	}
};