/*

Given a string which contains only lowercase letters, 

remove duplicate letters so that every letter appear once and only once. 

You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
    Given "bcabc"
    Return "abc"

    Given "cbacdcbc"
    Return "acdb"

*/

#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 24ms
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, vector<int>> indexes;
        string result;
        int n = s.length(), start = 0, end;
        for (int i = 0; i < n; ++i)
            indexes[s[i]].push_back(i);
        while (!indexes.empty())
        {
            end = n - 1;
            for (auto it = indexes.begin(); it != indexes.end(); ++it)
                end = min(end, it->second.back());  // smallest among the last index of each character

            // find out the smallest unused char until the "end" index as the next char
            char c = 'z' + 1;
            for (int i = start; i <= end; ++i)
                if (s[i] < c && indexes.find(s[i]) != indexes.end())
                {
                    c = s[i];
                    start = i + 1;
                }
            result += c;
            indexes.erase(c);
        }

        return result;
    }
};