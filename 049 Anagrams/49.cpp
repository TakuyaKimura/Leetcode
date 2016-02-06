/*

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:
    [
    ["ate", "eat","tea"],
    ["nat","tan"],
    ["bat"]
    ]

Note:
For the return value, each inner list's elements must follow the lexicographic order.
All inputs will be in lower-case.

*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        sort(strs.begin(), strs.end());
        unordered_map<string, int> idx2result;
        vector<vector<string>> result;
        string sortedStr;
        int idx = 0;
        for (auto& str : strs)
        {
            sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end());
            if (idx2result.find(sortedStr) != idx2result.end())
                result[idx2result[sortedStr]].push_back(str);
            else
            {
                idx2result[sortedStr] = idx++;
                result.push_back({ str });
            }
        }
        return result;
    }
};