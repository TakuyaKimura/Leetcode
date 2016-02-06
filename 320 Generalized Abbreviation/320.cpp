/*

Write a function to generate the generalized abbreviations of a word.

Example:
Given word = "word", return the following list (order does not matter):
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

*/

#include <vector>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

// total number of abbrevations
// C(n, 0) + C(n, 1) + ... + C(n, n) = 2^n
// because they are binomial coefficients

// dfs and backtracking, 64ms
class Solution {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> result;
		dfs(word, 0, (int)word.length() - 1, result);
		return result;
	}
private:
	void dfs(string word, int start, int end, vector<string>& result) {
		if (start > end)
		{
			result.push_back(word);
			return;
		}
		string save = word;
		dfs(word, start + 1, end, result);  // len == 0
		for (int len = 1; len <= end - start + 1; ++len)
		{
			word = save;  // before replacing anything
			word.replace(start, len, to_string(len));
			dfs(word, start + log10(len) + 2, end - len + log10(len) + 1, result);  // recalculate start and end
		}
	}
};

// bit manipulation, 108ms
// e.g., for "word": 0110 -> w11d -> w2d
class Solution2 {
public:
	vector<string> generateAbbreviations(string word) {
		int n = word.length(), size = 1 << n;
		vector<string> result(size);
		for (int i = 0; i < size; ++i)
		{
			ostringstream ss;
			int count = 0;
			for (int j = 0; j < n; ++j)
			{
				if (i & (1 << j))  // abbreviate
					++count;
				else               // don't abbreviate
				{
					if (count)
					{
						ss << count;
						count = 0;
					}
					ss << word[j];
				}
			}

			if (count)  // don't forget
				ss << count;

			result[i] = ss.str();
		}
		return result;
	}
};