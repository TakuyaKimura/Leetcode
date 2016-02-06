/*

Given a string S, find the longest palindromic substring in S. 
You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

*/

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// fastest, 4ms
class Solution3 {
public:
    string longestPalindrome(string s) {
        int n = s.length(), start = 0, max_len = 1, new_len, i = 0;
        while (i < n)
        {
            // n-i + n-i-1 <= max_len (the longest possible centered at i, centered at i-1 and i would already been caught when centered at i-1)
            if (n - i <= (max_len + 1) / 2)
                break;
            int j = i, k = i;
            while (k < n - 1 && s[k + 1] == s[k])
                ++k; // Skip duplicate characters.
            i = k + 1;  // next center!!!!!!!!!!!!!!!!!!!!!
            while (k < n - 1 && j > 0 && s[k + 1] == s[j - 1])
            {
                ++k;
                --j;
            } // Expand.
            new_len = k - j + 1;
            if (new_len > max_len)
            {
                start = j;
                max_len = new_len;
            }
        }
        return s.substr(start, max_len);
    }
};

// a palindrome mirrors around its center
// there are at most 2*n-1 centers (in-between characters)
// 64ms
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length(), len = 1;
        string longest = s.substr(0, 1), expanded;
        for (int i = 0; i < n - 1; ++i)  // don't need to expand the last character
        {
            expanded = expandAroundCenter(s, i, i);
            if (expanded.length() > len)
            {
                longest = expanded;
                len = expanded.length();
            }
            expanded = expandAroundCenter(s, i, i + 1);
            if (expanded.length() > len)
            {
                longest = expanded;
                len = expanded.length();
            }
        }
        return longest;
    }
private:
    string expandAroundCenter(string& s, int c1, int c2) {
        while (c1 >= 0 && c2 < s.length() && s[c1] == s[c2])
        {
            --c1;
            ++c2;
        }
        return s.substr(c1 + 1, c2 - c1 - 1);
    }
};

// Manacher¡¯s Algorithm O(n)
// in stead of expanding at every center, we could use the symmetric property of a palindrome
// to avoid repeated computation
// http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// 8ms

class Solution2 {
public:
    string longestPalindrome(string s) {
        string t = preProcess(s);
        int n = t.length(), center = 0, right = 0;
        vector<int> p(n, 0);  // length of the palindrome centers at i, it's just the distance from center (exclusive) to the right / left
        // or int *p = new int[n]; delete[] p;

        for (int i = 1; i < n - 1; ++i)
        {
            int i_mirror = 2 * center - i;  // c - (i - c)

            p[i] = (right > i) ? min(right - i, p[i_mirror]) : 0;

            // Attempt to expand palindrome centered at i
            while (t[i + p[i] + 1] == t[i - p[i] - 1])
                ++p[i];

            // If palindrome centered at i expands past R, adjust center based on expanded palindrome
            if (i + p[i] > right)
            {
                center = i;
                right = i + p[i];
            }
        }

        // find the maximum in p
        int maxLen = 0, centerIdx = 0;
        for (int i = 1; i < n - 1; ++i)
        {
            if (p[i] > maxLen)
            {
                maxLen = p[i];
                centerIdx = i;
            }
        }
        return s.substr((centerIdx - 1 - maxLen) / 2, maxLen);
    }
private:
    // For example, "abba" -> "^#a#b#b#a#$"
    // ^ and $ signs are sentinels appended to each end to avoid bounds checking
    string preProcess(string s) {
        if (s.empty())
            return "^$";
        ostringstream out;
        out << '^';
        for (char c : s)
            out << '#' << c;
        out << "#$";
        return out.str();
    }
};