/*

Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

*/

#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 12ms
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        int count[26] {0};
        for (auto c : s)
            ++count[c - 'a'];
        for (auto c : t)
        {
            if (count[c - 'a'] == 0)
                return false;
            --count[c - 'a'];
        }
        return true;
    }
};

// speed up the sorting procedure from 68ms to 48ms
class Solution2 {
    bool isAnagram(string s, string t) {
        sort((char*)s.c_str(), (char*)s.c_str() + s.size());  // sort(s.begin(), s.end());
        sort((char*)t.c_str(), (char*)t.c_str() + t.size());  // sort(t.begin(), t.end());
        return s == t;
    }
};

// 36ms
class Solution3 {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        unordered_map<char, int> counts;
        for (auto c : s)
            ++counts[c];
        for (auto c : t)
            --counts[c];

        for (auto count : counts)
            if (count.second)
                return false;
        return true;
    }
};