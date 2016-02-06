/*

Given a string, find the length of the longest substring without repeating characters. 
For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. 
For "bbbbb" the longest substring is "b", with the length of 1.

*/

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

// fastest
class Solution4 {
public:
    int lengthOfLongestSubstring(string s) {
        int pos[128], start = 0, i = 0, n = s.length(), longest = 0;
        memset(pos, -1, sizeof(pos));
        for (i = 0; i < n; ++i)
        {
            char c = s[i];
            if (pos[c] >= start)  // have duplicates in the range
            {
                longest = max(longest, i - start);  // only update when we have duplicates in the range
                start = pos[c] + 1;
            }
            pos[c] = i;
        }
        return max(longest, i - start);
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int longest = 0, n = s.length();
        vector<int> hash(128, -1);  // use this as hashtable to store the pos of last time it appears
        for (int i = 0, j = 0; j < n; ++j)  // i denotes the start point
        {
            i = max(i, hash[s[j]] + 1);  // if last time it appears is before i, we don't update i
            hash[s[j]] = j;
            longest = max(longest, j - i + 1);
        }
        return longest;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        int longest = 0, n = s.length(), len = 0;
        vector<int> hash(128, -1);  // use this as hashtable to store the pos of last time it appears
        for (int i = 0, j = 0; j < n; ++j)  // i denotes the start point
        {
            if (hash[s[j]] >= i)
            {
                if (len > longest)
                    longest = len;
                i = hash[s[j]] + 1;
                len = j - i;
            }
            hash[s[j]] = j;
            ++len;
        }
        if (len > longest)
            longest = len;
        return longest;
    }
};

// much slower
class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        int longest = 0, n = s.length();
        unordered_map<char, int> hash;
        for (int i = 0, j = 0; j < n; ++j)  // i denotes the start point
        {
            if (hash.find(s[j]) != hash.end())
                i = max(i, hash[s[j]] + 1);  // if last time it appears is before i, we don't update i
            hash[s[j]] = j;
            longest = max(longest, j - i + 1);
        }
        return longest;
    }
};