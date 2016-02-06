/*

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
    bool isMatch(const char *s, const char *p)

Some examples:
    isMatch("aa","a") ¡ú false
    isMatch("aa","aa") ¡ú true
    isMatch("aaa","aa") ¡ú false
    isMatch("aa", "a*") ¡ú true
    isMatch("aa", ".*") ¡ú true
    isMatch("ab", ".*") ¡ú true
    isMatch("aab", "c*a*b") ¡ú true

*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty())
            return s.empty();

        if (p.length() > 1 && '*' == p[1])
            return (isMatch(s, p.substr(2)) ||
                !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p)
                );
        else
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }
};

class Solution2 {
public:
    bool isMatch(string s, string p) {
        /**
        * f[i][j]: if s[0..i-1] matches p[0..j-1]
        * if p[j - 1] != '*'
        *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
        * if p[j - 1] == '*', denote p[j - 2] with x
        *      f[i][j] is true iff any of the following is true
        *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
        *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
        * '.' matches any single character
        */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

        f[0][0] = true;
        for (int i = 1; i <= m; ++i)
            f[i][0] = false;
        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
        for (int j = 2; j <= n; ++j)
            f[0][j] = '*' == p[j - 1] && f[0][j - 2];

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                else
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

        return f[m][n];
    }
};

// fastest
// checking from the back
// f1/f2[n] - matching 0 characters in s
// f1/f2[n-1] - matching 1 characters in s from the back
// ...
class Solution3 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        bool star = false, result;
        bool *f = new bool[2 * n + 2], *f1 = f, *f2 = f + n + 1;  // f1 previous round, f2 current round
        // each char in p except '*' is one round
        //fill_n(f, 2 * n + 2, false);
        fill(f, f + 2 * n + 2, false);

        f1[n] = true;  // 0 char in s matches 0 char in p

        for (int j = m - 1; j >= 0; --j) // m-j chars in p from the back
        {
            if (p[j] == '*')
            {
                star = true;
                continue;
            }
            else
            {
                if (!star)
                {
                    f2[n] = false;  // 0 char in s won't match m-j chars in p
                    for (int i = n - 1; i >= 0; --i)
                    {
                        if (s[i] == p[j] || (p[j] == '.'))
                            f2[i] = f1[i + 1];
                        else
                            f2[i] = false;
                    }
                }
                else
                {
                    f2[n] = f1[n];  // if 0 char in s matches m-j-1 chars in p
                    for (int i = n - 1; i >= 0; --i)
                    {
                        f2[i] = f1[i];
                        if (!f2[i] && (s[i] == p[j] || p[j] == '.'))
                            f2[i] = f2[i + 1];
                    }
                }
                star = false;
            }
            swap(f1, f2);
        }
        result = f1[0];
        delete[] f;
        return result;
    }
};

// modified from Solution3, more concise
class Solution4 {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        bool star = false, result;
        bool *f = new bool[2 * n + 2], *f1 = f, *f2 = f + n + 1;  // f1 previous round, f2 current round
        // each char in p except '*' is one round
        //fill_n(f, 2 * n + 2, false);
        fill(f, f + 2 * n + 2, false);

        f1[n] = true;  // 0 char in s matches 0 char in p

        for (int j = m - 1; j >= 0; --j) // m-j chars in p from the back
        {
            if (p[j] == '*')
            {
                star = true;
                continue;
            }
            else
            {
                if (!star)
                {
                    f2[n] = false;  // 0 char in s won't match m-j chars in p
                    for (int i = n - 1; i >= 0; --i)
                    {
                        if (s[i] == p[j] || (p[j] == '.'))
                            f2[i] = f1[i + 1];
                        else
                            f2[i] = false;
                    }
                }
                else
                {
                    f2[n] = f1[n];  // if 0 char in s matches m-j-1 chars in p
                    for (int i = n - 1; i >= 0; --i)
                    {
                        f2[i] = f1[i];
                        if (!f2[i] && (s[i] == p[j] || p[j] == '.'))
                            f2[i] = f2[i + 1];
                    }
                }
                star = false;
            }
            swap(f1, f2);
        }
        result = f1[0];
        delete[] f;
        return result;
    }
};

int main()
{
    Solution4 s;
    cout << s.isMatch("aa", "ab*");
}