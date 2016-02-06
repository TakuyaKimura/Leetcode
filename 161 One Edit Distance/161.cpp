/*

Given two strings S and T, determine if they are both one edit distance apart.

*/

#include <string>
using namespace std;

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.length(), n = t.length(), i = 0;
        if (m > n)
            return isOneEditDistance(t, s);

        if (n - m > 1 || s == t)
            return false;

        for (; i < m && s[i] == t[i]; ++i) {}

        if (m == n)
            s[i] = t[i];
        else
            s.insert(i, 1, t[i]);

        return s == t;
    }
};

// If it is a file or stream where you have iterator only moves forward, 
// and you only know the size when you hit the end, 
// we have to split into 3 cases when first difference occurs. 
// s.size() and t.size() are used in the code but they can be easily translated into iter!=s.end()
class Solution2 {
public:
    bool isOneEditDistance(string s, string t) {
        int i = 0;
        while (i < s.size() && i < t.size() && s[i] == t[i])
            ++i;

        if (i == s.size() && i == t.size())
            return false;
        if (i == s.size() && i + 1 == t.size() || i == t.size() && i + 1 == s.size())
            return true;
        if (i < s.size() && i < t.size())
        {
            ++i;
            bool s1 = true, s2 = true, s3 = true;  //3 senarios
            while (i < s.size() && i < t.size())
            {
                if (s[i] != t[i - 1])  // insert in s
                    s1 = false;
                if (s[i] != t[i])      // substitute
                    s2 = false;
                if (s[i - 1] != t[i])  // delete in s
                    s3 = false;
                if (!s1 && !s2 && !s3)
                    return false;
                ++i;
            }
            if (s1 && i + 1 == s.size() && s[i] == t[i - 1])
                return true;
            if (s2 && i == s.size() && i == t.size())
                return true;
            if (s3 && i + 1 == t.size() && s[i - 1] == t[i])
                return true;
        }
        return false;
    }
};