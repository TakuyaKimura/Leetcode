/*

Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. 

Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

*/

#include <string>
#include <vector>
#include <algorithm>  // reverse or reverse_copy
using namespace std;

// O(n^2), 4ms
// find the length of the longest palindromic prefix substring
class Solution {
public:
    string shortestPalindrome(string s) {
		if (s.empty())
			return s;

        int n = s.length(), longest = 1, start, end, center = (n - 1) / 2;
        for (int i = 0; i <= center;)  // if i is in the right half, the substring can't be a prefix
        {
            start = end = i;

            // skip the duplicates, i is shifting to the right
            while (end < n - 1 && s[end + 1] == s[start])
                ++end;

            i = end + 1;

			while (end < n - 1 && start > 0 && s[end + 1] == s[start - 1])
				--start, ++end;

            // start == 0 means the palindromic substring is also prefix string.
			if (start == 0)
				longest = max(longest, end + 1);
        }

        // reverse the remaining substring and adding it in front of s.

        //string remaining = s.substr(longest, len - longest);
        //reverse(remaining.begin(), remaining.end());
		string remaining(n - longest, ' ');
		reverse_copy(s.begin() + longest, s.end(), remaining.begin());

        return remaining + s;
    }
};

// Time Limit Exceeded on large input (with the same character)
class Solution2 {
public:
	string shortestPalindrome(string s) {
		if (s.empty())
			return s;
		int n = s.length(), center = n / 2, start, end;  // the middle or the right middle
		for (int len = n;; --len)
		{
			start = (len - 1) / 2;
			end = len / 2;

			while (start >= 0 && end < n && s[start] == s[end])
				--start, ++end;
			if (start == -1)
				break;
		}
		string result(n - end, ' ');
		reverse_copy(s.begin() + end, s.end(), result.begin());
		return result + s;
	}
};

// KMP-based O(n) time & O(n) space
class Solution3 {
public:
    string shortestPalindrome(string s) {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s;

        vector<int> p(l.size(), 0);  // length of the longest proper prefix & suffix ending at i; this part is palindromic
        for (int i = 1; i < l.size(); ++i)
        {
            int j = p[i - 1];  // j is the next to the end of the prefix
            while (j > 0 && l[i] != l[j])
                j = p[j - 1];  // fall back
            p[i] = (j += l[i] == l[j]);
        }

        return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;  // substract the part which is palindromic itself
    }
};

// O(n) solution, based on Manacher's algorithm
// Such algorithm returns the maximum length of the palindrome string centered at i
// so we just need to find the maximum length palindrome string with the left end point at 0 
class Solution4 {
public:
    string shortestPalindrome(string s) {
        int len = s.size();
        string T = preProcess(s);
        const int n = T.length();
        vector<int> P(n);
        int i_mirror, C = 0, R = 0;

        for (int i = 1; i < n - 1; ++i)
        {
            i_mirror = 2 * C - i; // equals to i' = C - (i-C)

            P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0;

            // Attempt to expand palindrome centered at i
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
                ++P[i];

            // If palindrome centered at i expand past R,
            // adjust center based on expanded palindrome.
            if (i + P[i] > R)
            {
                C = i;
                R = i + P[i];
            }
        }

        // Just need to change this part from problem 5
        int maxLen = 0, centerIndex = 0;
        for (int i = 1; i < n - 1; ++i)
            if (1 == i - P[i])  // left end is the first character
                maxLen = P[i];

        string temp = s.substr(maxLen);  // the rest on the right
        reverse(temp.begin(), temp.end());
        return temp + s;
    }

private:

    // Transform S into T.
    // For example, S = "abba", T = "^#a#b#b#a#$".
    // ^ and $ signs are sentinels appended to each end to avoid bounds checking
    string preProcess(string s) {
        int n = s.length();
        if (n == 0)
            return "^$";
        string ret(2 * n + 3, '#');
        ret[0] = '^';
        ret[2 * n + 2] = '$';
        for (int i = 1; i <= n; ++i)
            ret[2 * i] = s[i - 1];

        return ret;
    }
};