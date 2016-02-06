/*

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) 
where the two words do not share common letters. 

You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.

Follow up:
Could you do better than O(n2), where n is the number of words?

*/

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// bit manipulation, 100ms
class Solution {
public:
	int maxProduct(vector<string>& words) {
		sort(words.begin(), words.end(), [](const string& s1, const string& s2){ return s1.length() < s2.length(); });
		int n = words.size();
		size_t maxProd = 0;  // same type as word.length()
		vector<int> letters(n);
		for (int i = 0; i < n; ++i)
		{
			int x = 0;
			for (char c : words[i])
				x |= 1 << (c - 'a');
			letters[i] = x;

			for (int j = i - 1; j >= 0; --j)
				if ((x & letters[j]) == 0)  // note the precedence
				{
					maxProd = max(maxProd, words[i].length() * words[j].length());
					break;  // words[j].length() is gonna be smaller for the rest j's
				}		
		}
		return maxProd;
	}
};

// 108ms
class Solution2 {
public:
	int maxProduct(vector<string>& words) {
		sort(words.begin(), words.end(), [](const string& s1, const string& s2){ return s1.length() < s2.length(); });
		int n = words.size();
		size_t maxProd = 0;  // same type as word.length()
		vector<int> letters(n);
		for (int i = n - 1; i >= 0; --i)
		{
			size_t i_len = words[i].length();
			int x = 0;
			for (char c : words[i])
				x |= 1 << (c - 'a');
			letters[i] = x;

			for (int j = n - 1; j > i && i_len * words[j].length() > maxProd; --j)
				if ((x & letters[j]) == 0)  // note the precedence
				{
					maxProd = max(maxProd, i_len * words[j].length());
					break;  // words[j].length() is gonna be smaller for the rest j's
				}
		}
		return maxProd;
	}
};