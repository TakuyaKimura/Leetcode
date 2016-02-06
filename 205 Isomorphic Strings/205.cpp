/*

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
    Given "egg", "add", return true.

    Given "foo", "bar", return false.

    Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

*/

#include <unordered_map>
using namespace std;

// use a number as a code to represent the corresponding letter in s and t
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int codeS[128] {0}, codeT[128] {0};
        int n = s.length();
        for (int i = 0; i < n; ++i)
        {
            if (codeS[s[i]] != codeT[t[i]])
                return false;
            if (codeS[s[i]] == 0)  // ==, both are 0
                codeS[s[i]] = codeT[t[i]] = i + 1;
        }
        return true;
    }
};

// slow
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> smap, tmap;
        int len = s.length();
        for (int i = 0; i < len; ++i)
        {
            if (smap.find(s[i]) == smap.end() && tmap.find(t[i]) == tmap.end())
            {
                smap[s[i]] = t[i];
                tmap[t[i]] = s[i];
            }
            else if (smap.find(s[i]) != smap.end() && smap[s[i]] == t[i])  // it must be the case that tmap[t[i]] == s[i]
                continue;
            else
                return false;
        }
        return true;
    }
};