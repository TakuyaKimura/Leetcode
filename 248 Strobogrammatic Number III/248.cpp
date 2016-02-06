/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

Note:
Because the range might be a large number, the low and high numbers are represented as string.

*/

#include <vector>
using namespace std;

class Solution {
public:
	int strobogrammaticInRange(string low, string high) {
		addOne(high);
		int n1 = low.length(), n2 = high.length(), result = 0;
		if (n1 > n2 || n1 == n2 && low >= high)
			return 0;
		char pairs[5][2] {{ '0', '0' }, { '1', '1' }, { '6', '9' }, { '8', '8' }, { '9', '6' } };
		vector<int> dp(n2 + 1, 0);
		fillDP(dp);
		for (int len = n1; len < n2; ++len)
			result += dp[len + 1] - dp[len - 1];
		return result - strobogrammaticLessThan(low, false, pairs, dp) + strobogrammaticLessThan(high, false, pairs, dp);
	}

private:
	// allow 0 at the front, use dp[len + 1] to access
	void fillDP(vector<int>& dp) {
		int n = dp.size();
		if (n > 1)
			dp[1] = 1;
		if (n > 2)
			dp[2] = 3;
		for (int i = 3; i < n; ++i)
			dp[i] = dp[i - 2] * 5;
	}

	void addOne(string& s) {
		if (s.empty())
			return;
		int i = s.length() - 1;
		while (i >= 0 && s[i] == '9')
			s[i--] = '0';
		if (i < 0)
			s = '1' + s;
		++s[i];
	}

	// number of strobogrammatics that are of the same length and are strictly less than s
	int strobogrammaticLessThan(string s, bool allowZero, char(&pairs)[5][2], vector<int>& dp) {
		int n = s.length(), count = 0;
		if (n == 0 || s == "0")
			return 0;
		if (n == 1)
		{
			if (s == "1")
				return 1;
			if (s < "7")
				return 2;
			if (s < "9")
				return 3;
			return 4;
		}

		char first = s[0], last = s[n - 1];
		for (int i = 1 - allowZero; i < 5; ++i)
		{
			if (pairs[i][0] < first)
				count += dp[n - 1];
			else if (pairs[i][0] > first)
				break;
			else
			{
				string sub = s.substr(1, n - 2);
				if (last > pairs[i][1])
					addOne(sub);
				count += strobogrammaticLessThan(sub, true, pairs, dp);
			}
		}
		return count;
	}
};